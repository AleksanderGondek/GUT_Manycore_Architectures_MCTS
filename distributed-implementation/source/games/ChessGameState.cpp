//
// Created by agondek on 12/12/15.
//

#include "ChessGameState.h"

namespace Mcts
{
    namespace GameStates
    {
        ChessGameState::ChessGameState(unsigned short int lastActivePlayer,
                                       std::unordered_map<std::string, std::string> chessBoard)
        {
            this->setLastActivePlayer(lastActivePlayer);
            this->setChessBoard(chessBoard);
        }

        IGameState* ChessGameState::clone(void)
        {
            return new ChessGameState(this->getLastActivePlayer(), this->_chessBoard);
        }

        void ChessGameState::setChessBoard(std::unordered_map<std::string, std::string> chessBoard)
        {
            this->_chessBoard = chessBoard;
        }

        unsigned long int ChessGameState::getStateValue(unsigned short int playerId)
        {
            if(playerId == MCTS_PLAYER_ONE_ID)
            {
                return this->_playerTwoKingDown ? 1 : 0;
            }
            else if(playerId == MCTS_PLAYER_TWO_ID)
            {
                return this->_playerOneKingDown ? 1 : 0;
            }

            return 0;
        }

        void ChessGameState::performAction(std::string action)
        {
            // Because of format '{playerId}>{fromPostion}>{toPostion}'
            // i.e. 1>1A>1B
            std::string pieceFromPosition = action.substr(2,2);
            std::string pieceToPosition = action.substr(5,2);
            bool toPostionIsEmpty = IsBoardFieldEmpty(pieceToPosition);

            if(!toPostionIsEmpty)
            {
                // TODO: Later this shoud not take place
                // But for now game ends when king is dead
                std::string pieceToData = this->_chessBoard[pieceToData];
                if (pieceToData.substr(2, 1) == MCTS_CHESS_GAME_PIECE_KING)
                {
                    // Taken down king will belong to lastActivePlayer, since current
                    // turn is not his.
                    if (this->_lastActivePlayer == MCTS_PLAYER_ONE_ID)
                    {
                        this->_playerOneKingDown = true;
                    }
                    else if (this->_lastActivePlayer == MCTS_PLAYER_TWO_ID)
                    {
                        this->_playerTwoKingDown = true;
                    }
                }
            }

            // Move piece to pointed location
            this->_chessBoard[pieceToPosition] = this->_chessBoard[pieceFromPosition];

            if(!toPostionIsEmpty)
            {
                // Remove piece from previous location
                this->_chessBoard.erase(pieceFromPosition);
            }
        }

        // This function has many uses and should be splitted into multiple
        // However for nows this should do.
        // And again: for now, we are not checking for checks - whatever happens, happens
        std::vector<std::string> ChessGameState::getAvailableActions(void)
        {
            // If king is down, game is over, no further moves are permitted
            if(this->_playerOneKingDown || this->_playerTwoKingDown)
            {
                return std::vector<std::string>();
            }

            // Calculate all actions for given player
            for (std::unordered_map<std::string, std::string>::iterator it = this->_chessBoard.begin();
                 it != this->_chessBoard.end(); ++it)
            {
                std::vector<std::string> newActions = this->getAvailableActions(it->first, it->second);
                this->_availableActions.insert(
                        this->_availableActions.end(),
                        newActions.begin(),
                        newActions.end()
                );
            }

            return std::vector<std::string>();
        }

        std::vector<std::string> ChessGameState::getAvailableActions(std::string piecePosition,
                                                                     std::string pieceData)
        {
            std::string pieceType = pieceData.substr(2,1);
            if(MCTS_CHESS_GAME_PIECE_PAWN == pieceType)
            {
                return this->GetPawnPossibleMoves(piecePosition, pieceData);
            }
            else if(MCTS_CHESS_GAME_PIECE_KNIGHT == pieceType)
            {
                return std::vector<std::string>();
            }
            else if(MCTS_CHESS_GAME_PIECE_BISHOP == pieceType)
            {
                return std::vector<std::string>();
            }
            else if(MCTS_CHESS_GAME_PIECE_ROOK == pieceType)
            {
                return std::vector<std::string>();
            }
            else if(MCTS_CHESS_GAME_PIECE_QUEEN == pieceType)
            {
                return std::vector<std::string>();
            }
            else if(MCTS_CHESS_GAME_PIECE_KING == pieceType)
            {
                return this->GetKingPossibleMoves(piecePosition, pieceData);
            }

            return std::vector<std::string>();
        }

        std::vector<std::string> ChessGameState::GetKingPossibleMoves(std::string kingPosition,
                                                                      std::string kingData)
        {
            std::vector<std::string> moves;
            // Because pawnPostion '1A'
            char posLetter = kingPosition[1];
            int posIndex = atoi(&kingPosition[0]);
            // Because pawnData '1:R'
            int controlingPlayer = atoi(&kingData[0]);

            // make sure that numberIndex is above 0
            int numberIndex = (posIndex - 1) > 0 ? posIndex - 1 : posIndex;
            int numberIndexMax = (posIndex + 1) <= 8 ? posIndex + 1 : posIndex;
            // make sure that letterIndex is not smaller than 'A'
            char letterIndex = (posLetter - 1) >= 'A' ? posLetter - 1 : posLetter;
            char letterIndexMax = (posLetter + 1) <= 'Z' ? posLetter + 1 : posLetter;

            // Check 1x1 square around king for possible moves
            while(numberIndex <= numberIndexMax)
            {
                while(letterIndex <= letterIndexMax)
                {
                    std::string newPosition = std::to_string(numberIndex);
                    newPosition += letterIndex;

                    // If place is empty
                    if(this->IsBoardFieldEmpty(newPosition))
                    {
                        std::string action = std::to_string(controlingPlayer);
                        action += ">";
                        action += kingPosition;
                        action += ">";
                        action += newPosition;
                        moves.push_back(action);
                    }
                    // If place is occupied
                    else
                    {
                        std::string pieceToBeTaken = this->_chessBoard[newPosition];
                        unsigned short int pieceToBeTakenOwnerId = (unsigned short int)
                                std::strtoul(pieceToBeTaken.substr(0,1).c_str(), 0, 10);

                        // If occupied place is not owned by same player
                        if(pieceToBeTakenOwnerId != controlingPlayer)
                        {
                            std::string action = std::to_string(controlingPlayer);
                            action += ">";
                            action += kingPosition;
                            action += ">";
                            action += newPosition;
                            moves.push_back(action);
                        }
                    }
                    letterIndex += 1;
                }
                numberIndex++;
            }

            return moves;
        }

        std::vector<std::string> ChessGameState::GetPawnPossibleMoves(std::string pawnPosition,
                                                                      std::string pawnData)
        {
            std::vector<std::string> moves;
            // Because pawnPostion '1A'
            char posLetter = pawnPosition[1];
            char newPosLetter = pawnPosition[1];
            int newPosIndex = atoi(&pawnPosition[0]);
            // Because pawnData '1:R'
            int controlingPlayer = atoi(&pawnData[0]);


            // Pawns of player 1 move from index 1st towards 8th index,
            // pawns of player 2 move from index 8th towards 1st index
            if(controlingPlayer == MCTS_PLAYER_ONE_ID)
            {
                // If field ahead exists
                newPosIndex++;
                if(newPosIndex <= 8)
                {
                    std::string newPosition = std::to_string(newPosIndex);
                    newPosition += newPosLetter;
                    // If field ahead is empty
                    if(this->IsBoardFieldEmpty(newPosition))
                    {
                        std::string action = std::to_string(controlingPlayer);
                        action += ">";
                        action += pawnPosition;
                        action += ">";
                        action += newPosition;

                        moves.push_back(action);
                    }

                    // If can takeout other piece
                    newPosition = std::to_string(newPosIndex);
                    newPosLetter += 1;
                    newPosition += newPosLetter;
                    if(newPosLetter <= 'H')
                    {
                        // If field is not empty (cannot take down nothing)
                        if(!this->IsBoardFieldEmpty(newPosition))
                        {
                            std::string pieceToBeTaken = this->_chessBoard[newPosition];
                            unsigned short int pieceToBeTakenOwnerId = (unsigned short int)
                                    std::strtoul(pieceToBeTaken.substr(0,1).c_str(), 0, 10);

                            if(pieceToBeTakenOwnerId != MCTS_PLAYER_ONE_ID)
                            {
                                std::string action = std::to_string(controlingPlayer);
                                action += ">";
                                action += pawnPosition;
                                action += ">";
                                action += newPosition;

                                moves.push_back(action);
                            }
                        }
                    }

                    newPosition = std::to_string(newPosIndex);
                    newPosLetter = posLetter;
                    newPosLetter -= 1;
                    newPosition += newPosLetter;
                    if(newPosLetter >= 'A')
                    {
                        // If field is not empty (cannot take down nothing)
                        if(!this->IsBoardFieldEmpty(newPosition))
                        {
                            // If field is not empty (cannot take down nothing)
                            if(!this->IsBoardFieldEmpty(newPosition))
                            {
                                std::string pieceToBeTaken = this->_chessBoard[newPosition];
                                unsigned short int pieceToBeTakenOwnerId = (unsigned short int)
                                        std::strtoul(pieceToBeTaken.substr(0,1).c_str(), 0, 10);

                                if(pieceToBeTakenOwnerId != MCTS_PLAYER_ONE_ID)
                                {
                                    std::string action = std::to_string(controlingPlayer);
                                    action += ">";
                                    action += pawnPosition;
                                    action += ">";
                                    action += newPosition;

                                    moves.push_back(action);
                                }
                            }
                        }
                    }
                }
            }
            else if(controlingPlayer == MCTS_PLAYER_TWO_ID)
            {
                // If field ahead exists
                newPosIndex--;
                if(newPosIndex > 0)
                {
                    std::string newPosition = std::to_string(newPosIndex);
                    newPosition += newPosLetter;
                    // If field ahead is empty
                    if(this->IsBoardFieldEmpty(newPosition))
                    {
                        std::string action = std::to_string(controlingPlayer);
                        action += ">";
                        action += pawnPosition;
                        action += ">";
                        action += newPosition;

                        moves.push_back(action);
                    }

                    // If can takeout other piece
                    newPosition = std::to_string(newPosIndex);
                    newPosLetter += 1;
                    newPosition += newPosLetter;
                    if(newPosLetter <= 'H')
                    {
                        // If field is not empty (cannot take down nothing)
                        if(!this->IsBoardFieldEmpty(newPosition))
                        {
                            std::string pieceToBeTaken = this->_chessBoard[newPosition];
                            unsigned short int pieceToBeTakenOwnerId = (unsigned short int)
                                    std::strtoul(pieceToBeTaken.substr(0,1).c_str(), 0, 10);

                            if(pieceToBeTakenOwnerId != MCTS_PLAYER_ONE_ID)
                            {
                                std::string action = std::to_string(controlingPlayer);
                                action += ">";
                                action += pawnPosition;
                                action += ">";
                                action += newPosition;

                                moves.push_back(action);
                            }
                        }
                    }

                    newPosition = std::to_string(newPosIndex);
                    newPosLetter = posLetter;
                    newPosLetter -= 1;
                    newPosition += newPosLetter;
                    if(newPosLetter >= 'A')
                    {
                        // If field is not empty (cannot take down nothing)
                        if(!this->IsBoardFieldEmpty(newPosition))
                        {
                            // If field is not empty (cannot take down nothing)
                            if(!this->IsBoardFieldEmpty(newPosition))
                            {
                                std::string pieceToBeTaken = this->_chessBoard[newPosition];
                                unsigned short int pieceToBeTakenOwnerId = (unsigned short int)
                                        std::strtoul(pieceToBeTaken.substr(0,1).c_str(), 0, 10);

                                if(pieceToBeTakenOwnerId != MCTS_PLAYER_ONE_ID)
                                {
                                    std::string action = std::to_string(controlingPlayer);
                                    action += ">";
                                    action += pawnPosition;
                                    action += ">";
                                    action += newPosition;

                                    moves.push_back(action);
                                }
                            }
                        }
                    }

                }
            }

            return moves;
        }

        std::string ChessGameState::GetPieceTypeFromBoardValue(std::string value)
        {
            // This nighmarish if chain is needed to make sure that we
            // are not returning invalid piece type if something goes
            // wrong. Then we can just return unknown type.

            std::string pieceType = value.substr(2,1);
            if(MCTS_CHESS_GAME_PIECE_PAWN == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_PAWN;
            }
            else if(MCTS_CHESS_GAME_PIECE_KNIGHT == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_KNIGHT;
            }
            else if(MCTS_CHESS_GAME_PIECE_BISHOP == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_BISHOP;
            }
            else if(MCTS_CHESS_GAME_PIECE_ROOK == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_ROOK;
            }
            else if(MCTS_CHESS_GAME_PIECE_QUEEN == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_QUEEN;
            }
            else if(MCTS_CHESS_GAME_PIECE_KING == pieceType)
            {
                return MCTS_CHESS_GAME_PIECE_KING;
            }

            return MCTS_CHESS_GAME_PIECE_UNKNOWN;
        }

        bool ChessGameState::IsBoardFieldEmpty(std::string position)
        {
            return this->_chessBoard.find(position) == this->_chessBoard.end();
        }

        // Getters and setters
        unsigned short int ChessGameState::getLastActivePlayer(void)
        {
            return this->_lastActivePlayer;
        }

        void ChessGameState::setLastActivePlayer(unsigned short int playerId)
        {
            this->_lastActivePlayer = playerId;
        }
    }
}
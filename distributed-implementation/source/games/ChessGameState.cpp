//
// Created by agondek on 12/12/15.
//

#include "ChessGameState.h"

namespace Mcts
{
    namespace GameStates
    {
        void ChessGameState::setChessBoard(std::unordered_map<std::string, std::string> chessBoard)
        {
            this->_chessBoard = chessBoard;
        }

        // This function has many uses and should be splitted into multiple
        // However for nows this should do.
        // And again: for now, we are not checking for checks - whatever happens, happens
        std::vector<std::string> ChessGameState::getAvailableActions(unsigned short int playerId)
        {
            // Calculate all actions for given player
            for (std::unordered_map<std::string, std::string>::iterator it = this->_chessBoard.begin();
                 it != this->_chessBoard.end(); ++it)
            {
                std::string playerString = (std::string)(it->second);
                unsigned short int player = (unsigned short int)
                        std::strtoul(playerString.substr(0,1).c_str(), 0, 10);
                if(player == MCTS_PLAYER_ONE_ID)
                {
                    std::vector<std::string> newActions = this->getAvailableActions(it->first, it->second);
                    this->_playerOneAvailableActions.insert(
                            this->_playerOneAvailableActions.end(),
                            newActions.begin(),
                            newActions.end()
                    );
                }
                else if(player == MCTS_PLAYER_TWO_ID)
                {
                    std::vector<std::string> newActions = this->getAvailableActions(it->first, it->second);
                    this->_playerTwoAvailableActions.insert(
                            this->_playerTwoAvailableActions.end(),
                            newActions.begin(),
                            newActions.end()
                    );
                }
            }

            if(playerId == MCTS_PLAYER_ONE_ID)
            {
                return this->_playerOneAvailableActions;
            }
            else if (playerId == MCTS_PLAYER_TWO_ID)
            {
                return this->_playerTwoAvailableActions;
            }

            std::vector<std::string> noActionsVector;
            noActionsVector.push_back(MCTS_ACTION_NOT_AVAILABLE);
            return noActionsVector;
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
                return std::vector<std::string>();
            }

            return std::vector<std::string>();
        }

        std::vector<std::string> ChessGameState::GetPawnPossibleMoves(std::string pawnPosition,
                                                                      std::string pawnData)
        {
            std::vector<std::string> moves;
            // Because pawnPostion '1A'
            char posLetter = pawnPosition[1];
            char newPosLetter = pawnPosition[1];
            int posIndex = atoi(&pawnPosition[0]);
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
                        std::string action = pawnPosition;
                        action += "|";
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
                                std::string action = pawnPosition;
                                action += "|";
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
                                    std::string action = pawnPosition;
                                    action += "|";
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
                        std::string action = pawnPosition;
                        action += "|";
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
                                std::string action = pawnPosition;
                                action += "|";
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
                                    std::string action = pawnPosition;
                                    action += "|";
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
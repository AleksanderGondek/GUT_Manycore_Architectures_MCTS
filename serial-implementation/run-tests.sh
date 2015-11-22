#!/bin/sh

# Install serial-implementation package
cd ./source
python setup.py develop

# Go back and run tests
cd ..
py.test
test_status=$?

# Uninstall serial-implementation package
cd ./source
python setup.py develop --uninstall
cd ..

# Go back to root dir
cd ..

exit ${test_status}

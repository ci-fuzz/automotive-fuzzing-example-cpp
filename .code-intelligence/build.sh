set -e
mkdir -p $WORK_DIR
cd $WORK_DIR
mkdir -p .cifuzz

cmake -DCIFUZZ_INSTALL_ROOT=/opt/ci-fuzz-2.30.0 ..
make -j$(nproc)
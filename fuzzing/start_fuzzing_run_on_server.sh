#/bin/sh
# Prerequisite for this script is that cictl login was executed!


#CIFUZZ_SERVER=grpc.code-intelligence.com
#PROJECT_NAME=

CIFUZZ_SERVER=127.0.0.1:80
PROJECT_NAME=projects/automotive-fuzzing-example-cpp-2ce2a824

# Build artifact
echo "Building artifact:"
fuzzing/create_artifact.sh
# Upload artifact to server
echo "Uploading artifact to server:"
ARTIFACT_NAME=$(cictl --server $CIFUZZ_SERVER import artifact my_fuzz_test_1.tar.gz -p $PROJECT_NAME)
# Start fuzzing run
echo "Starting fuzzing run:"
cictl --server $CIFUZZ_SERVER start $ARTIFACT_NAME
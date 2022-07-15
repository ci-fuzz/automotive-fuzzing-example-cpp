#!/bin/sh

MODUS=$1

if [ $MODUS = "template" ]; then
  COMPILE_COMMANDS=$2
  if test -f "$COMPILE_COMMANDS"; then
      python3 fuzzing/filter_compile_commands.py -c $COMPILE_COMMANDS -f fuzzing/filter.txt
      /home/dte/.local/bin/testgen template_cc $PWD $COMPILE_COMMANDS
  else
    echo "Compile Commands JSON file not found!"
  fi
elif [ $MODUS = "code" ]; then
  EXCEL_SHEET=$2
  if test -f "$EXCEL_SHEET"; then
    /home/dte/.local/bin/testgen code $EXCEL_SHEET
  else
    echo "Excel Sheet not found!"
  fi
else
  echo "Only template or code are allowed as first parameter!"
  echo "Provided parameter: $MODUS"
fi
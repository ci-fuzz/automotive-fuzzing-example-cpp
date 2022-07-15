#!/usr/bin/env python3

import json
import os
import re
from argparse import ArgumentParser

def parse_compile_commands(compile_commands, filters, filter_assembly_files):
    compile_commands_file = open(compile_commands)
    data = json.loads(compile_commands_file.read())
    compile_commands_file.close()
    
    new_compile_commands = "[" 
    for json_object in data:
        should_be_removed = False
        # If we want to filter our all .s files do it here
        if filter_assembly_files:
            # Check if the output file ends with .s
            re_assembly_file = "[^ ]*\.s"
            if re.search(re_assembly_file, json_object['file']) != None:
                # Continuing here filters our this json_object 
                # because it is not added to the new json
                continue
        for filter_path in filters:
            re_path_sep = r'[\\/]'
            re_filter_path = filter_path.strip().replace('\\', '/').replace('/', re_path_sep)
            # Check if a file shall be removed
            if re_filter_path.endswith('.c') or re_filter_path.endswith('.cc') or re_filter_path.endswith('.cpp'):
                if re.search(re_filter_path, json_object['command']) != None:
                    should_be_removed = True
                    break
                continue
            # Check if a file in a directory shall be removed (plus include dirs)
            re_filter_path += re_path_sep
            re_incl_path = f" -I ?[^ ]*{re_filter_path}[^ ]*"
            re_source_file = f"{re_filter_path}[^ ]*\.[cs]"
            if re.search(re_source_file, json_object['command']) != None:
                should_be_removed = True
                break
            json_object['command'] = re.sub(re_incl_path, "", json_object['command'])
        if not should_be_removed:
            new_compile_commands += json.dumps(json_object)
            new_compile_commands += ","
    
    return new_compile_commands[:-1] + "]"

def main():
    parser = ArgumentParser()
    parser.add_argument("-c", "--compile_commands", dest="compile_commands", help="Path to compile_commands.json file", metavar="FILE", required=True)
    parser.add_argument("-f", "--filter", dest="filter_file", help="Path to file which contains list of paths to filter", metavar="FILE", required=True)
    parser.add_argument("-o", "--output", dest="output_file_name", help="Path to new compile_commands.json file. If this is not set the compile_commands.json will be overwritten", metavar="FILE", default="")
    parser.add_argument("-s", "--filter-assembly-files", dest="filter_assembly_files", help="If this is set, all .s files will be filtered from the compile_commands.json", action="store_true")
    args = parser.parse_args()

    filter_file = open(args.filter_file)
    filters = filter_file.readlines()
    output_file_name = args.output_file_name
    if output_file_name == "":
        output_file_name = args.compile_commands
    
    new_compile_commands = parse_compile_commands(args.compile_commands, filters, args.filter_assembly_files)
    
    output_file = open(output_file_name, "w")
    output_file.write(new_compile_commands)
    output_file.close()

if __name__ == "__main__":
    main()

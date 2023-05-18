import sys
import os

def format_cpp_file(file_path):
    # Read the content of the C++ file
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Process each line
    formatted_code = ""
    max_col_width = 36
    curr_line_len = 0
    for i in range(len(lines)):
        # Replace tabs and multiple spaces with a single space
        lines[i] = ' '.join(lines[i].split())
        line = lines[i].rstrip().lstrip()
        canMutate = False
        if not line.startswith('//') and not line.startswith("*") and '//' not in line and '/*' not in line:
            if line.endswith((';', '}', '{')):
                canMutate = True
        if canMutate:
            # Remove newline at the end of the line
            a = line.rstrip()
            if (curr_line_len + len(a) > max_col_width):
                formatted_code += "\n"
                curr_line_len = 0 
            curr_line_len += len(a)
            if (curr_line_len > max_col_width) :
                curr_line_len -= max_col_width
            formatted_code += line.rstrip() 
        else:
            formatted_code += "\n"
            formatted_code += line.rstrip()
            formatted_code += "\n"

    def replace_tabs_and_multiple_spaces(text):
        lines = text.split('\n')
        formatted_lines = []
        for line in lines:
            line = line.replace('\t', ' ')
            line = ' '.join(line.split())
            formatted_lines.append(line)
        formatted_text = '\n'.join(formatted_lines)
        return formatted_text

    def remove_empty_lines(text):
        lines = text.split('\n')
        non_empty_lines = [line for line in lines if line.strip()]
        return '\n'.join(non_empty_lines)

    formatted_code = remove_empty_lines(formatted_code)
    formatted_code = replace_tabs_and_multiple_spaces(formatted_code)

    # Write the modified content back to the file
    with open(file_path, 'w') as file:
        file.write(formatted_code)

def format_cpp_files_recursive(directory):
    # Iterate through all files and subdirectories in the given directory
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)

            # Apply format_cpp_file only to files ending with ".h"
            if file.endswith('.h'):
                format_cpp_file(file_path)

# Read the directory path from the command line argument
directory_path = sys.argv[1]
format_cpp_files_recursive(directory_path)

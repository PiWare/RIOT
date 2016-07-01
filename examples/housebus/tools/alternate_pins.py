#!/usr/bin/python

import os
import sys
import csv
import argparse
import traceback

if __name__ == "__main__":
    try:
        parser = argparse.ArgumentParser(description = 'Alternate function template generator from csv table.')
        parser.add_argument('--csv', type = str, help = 'CSV formatted input table', required = True)
    #   parser.add_argument('--symbol', type = str, help = 'Output file for generated KiCAD symbols', required = True)
    #   parser.add_argument('--desc', type = str, help = 'Output file for generated KiCAD symbol description', required = True)
    #   parser.add_argument('--template_path', type = str, help = 'Path to template symbols', required = True)
    #   parser.add_argument('--table_path', type = str, help = 'Path to table based symbols', required = True)
        args = parser.parse_args()

#       symbol_output = open(args.symbol, "w")
#       symbol_output.write("EESchema-LIBRARY Version 2.3\n#encoding utf-8\n")
#       desc_output = open(args.desc, "w")
#       desc_output.write('EESchema-DOCLIB Version 2.0\n')

        with open(args.csv, 'rb') as csvfile:
            table = csv.reader(csvfile, delimiter=',', quotechar='\"')

            first = 0
            for row in table:
                if len(row) == 17:
                    name = row[0]
                    index = int(name[2:])
                    prefix = "typedef pin_tag<"+str(index)+", gpio"+name[1]+"::base, alternate_t::AF"
                    
                    for i in range(1, 17):
                        for part in row[i].split("/"):
                            part = part.lower()
                            if len(part) > 1 and part != "eventout":
                                if not first:
                                    print "namespace", name, "{\n"
                                    first = 1

                                print prefix+str(i - 1)+"> "+part+";"

                    if first:
                        print("\n}\n")
                        first = 0

    except Exception as e:
        traceback.print_exc()
        sys.exit(2)


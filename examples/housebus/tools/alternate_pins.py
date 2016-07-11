#!/usr/bin/python

import csv
import argparse
import traceback

if __name__ == "__main__":
    try:
        parser = argparse.ArgumentParser(description = 'Alternate function template generator from csv table.')
        parser.add_argument('--csv', type = str, help = 'CSV formatted input table', required = True)
        args = parser.parse_args()

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
                        print "\n}\n"
                        first = 0

    except Exception as e:
        traceback.print_exc()
        sys.exit(2)


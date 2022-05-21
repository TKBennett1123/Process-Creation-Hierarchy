1. Authors: Kyle Bennett, Isabella Nieto
2. Project: Two versions of the process creation hierarchy
4. How to compile and run program:  
gcc -Wall -Werror -o pcb_v1 pcb_v1.c  
gcc -Wall -Werror -o pcb_v2 pcb_v2.c  
./pcb_v1 > pcb_v1_output.txt  
./pcb_v2 > pcb_v2_output.txt  
6. File list:
   * pcb_v1.c (Source code, version 1, PCB structure using linked lists)
   * pcb_v2.c (Source code, version 2, PCB structure avoiding linked lists)
   * pcb_v1_output.txt (Output file, Version 1, Raw data, each data point represents 1,000 cycles)
   * pcb_v2_output.txt (Output file, Version 2, Raw data, each data point represents 1,000 cycles)
   * Final.xlsx (Excel file, Compliation of data from all versions of raw data, compatible used in statistical analysis file)
   * Final.R (R file, File with commands for all statistical analysis)
   * 'Final Statistical Analysis.pdf' (PDF file containing write up, comparision, graphs, and statistical analysis of data found in both versions)

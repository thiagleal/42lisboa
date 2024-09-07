FT_LINE1=7
FT_LINE2=15

cat /etc/passwd | 
grep -v '^#' | 
awk 'NR % 2 == 0' | 
sort -r | 
awk -F: '{print $1}' | 
sed -n "${FT_LINE1},${FT_LINE2}p" | 
rev |
sed -z 's/\n/, /g' | 
sed -z 's/, $/./'


gpt corrigiu:

FT_LINE1=7
FT_LINE2=15

cat /etc/passwd | 
grep -v '^#' | 
awk 'NR % 2 == 0' | 
awk -F: '{print $1}' | 
rev | 
sort | 
sed -n "${FT_LINE1},${FT_LINE2}p" | 
paste -sd ',' - | 
sed 's/,/, /g' | 
sed 's/$/./'
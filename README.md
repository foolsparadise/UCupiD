## UCupidD.c  
C-Language command and linked-list demo  
此工程为有关C语言command及链表Demo，供学习使用，其中涉及command，链表，链表遍历，链表出栈入栈等等基本及其它细节  
## requirments 需求  
requirments.pdf and following example  
详细需求请看requirements.pdf文档，以下为需求举例  
``  
$ cat database.txt  
111223333,Rob,M,F,47,5,Dancing,Painting,63,165  
123456789,Bob,M,F,77,2,Baseball,Cooking,72,275  
194783218,Ann,F,M,28,9,Dancing,Painting,65,125  
222334444,Barbara,F,M,40,4,Jogging,Movies,64,145  
222334567,John,M,M,45,7,Cooking,Hiking,70,182  
555446767,Joan,F,M,69,1,Organizing,Writing,59,115  
622555555,Drewbert,M,M,59,6,Organizing,Fishing,68,170  
823810924,Andrew,M,F,25,4,Dancing,Painting,84,280  
622555556,Zeta,F,F,34,6,Organizing,Fishing,68,170  
823810925,Fran,F,F,25,10,Dancing,Painting,84,280  
847111411,Adam,M,M,82,7,Theatre,Sparring,72,200  
999999999,Aerith,F,M,22,1,Gardening,Cooking,63,100  
$ ./UCupiD database.txt 111223333  
$ cat match_111223333.txt  
Matches for user 111223333 (Rob):  
- 194783218 (Ann)  
- 222334444 (Barbara)  
$ ./UCupiD database.txt 622555556  
$ cat match_622555556.txt  
Matches for user 622555556 (Zeta):  
- 823810925 (Fran)  
$ ./UCupiD database.txt 000000000  
User with SID 000000000 not found  
$ ./UCupiD wrong_file.txt 000000000  
Error: cannot open wrong_file.txt  
$ ./UCupiD  
Usage: ./UCupiD db_file SID  
``  
## MIT  

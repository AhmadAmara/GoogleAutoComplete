## GoogleAutoComplete

I implemented the funtion :

vector<AutoCompleteData> GetBestKCompletions(const string& prefix);
which returns the best 5 matches for the given prefix.

## output example:
indexing files...
converting json files to map ...
please insert your prefix :
trelve

*********** runtime : 381 microseconds ***********

=======================
score : 10
completed : gaping mouths, the staring lustreless eyes, fascinated him. He knew in
 source : The picture of Dorian Gray.txt
offset : 7039
=======================
=======================
score : 8
completed : hundred and twelve years: and he died.
 source : Moses_and_the_Sages__Bible.txt
offset : 345
=======================
=======================
score : 8
completed : 14:4 Twelve years they served Chedorlaomer, and in the thirteenth year
 source : Moses_and_the_Sages__Bible.txt
offset : 989
=======================
=======================
score : 8
completed : twelve princes shall he beget, and I will make him a great nation.
 source : Moses_and_the_Sages__Bible.txt
offset : 1232
=======================
=======================
score : 8
completed : castles; twelve princes according to their nations.
 source : Moses_and_the_Sages__Bible.txt
offset : 2043
=======================


please insert your prefix :
surprise

*********** runtime : 46 microseconds ***********

=======================
score : 16
completed : 33:14 The sinners in Zion are afraid; fearfulness hath surprised the
 source : Moses_and_the_Sages__Bible.txt
offset : 59185
=======================
=======================
score : 16
completed : 48:41 Kerioth is taken, and the strong holds are surprised, and the
 source : Moses_and_the_Sages__Bible.txt
offset : 65725
=======================
=======================
score : 16
completed : surprised! how is Babylon become an astonishment among the nations!
 source : Moses_and_the_Sages__Bible.txt
offset : 66223
=======================
=======================
score : 16
completed : coldly, when he had recovered from his surprise. "I never thought you
 source : The picture of Dorian Gray.txt
offset : 1131
=======================
=======================
score : 16
completed : all the surprise of candour."
 source : The picture of Dorian Gray.txt
offset : 1177
=======================


please insert your prefix :
moses

*********** runtime : 42 microseconds ***********

=======================
score : 10
completed : The Second Book of Moses:  Called Exodus
 source : Moses_and_the_Sages__Bible.txt
offset : 4768
=======================
=======================
score : 10
completed : and he became her son. And she called his name Moses: and she said,
 source : Moses_and_the_Sages__Bible.txt
offset : 4863
=======================
=======================
score : 10
completed : 2:11 And it came to pass in those days, when Moses was grown, that he
 source : Moses_and_the_Sages__Bible.txt
offset : 4866
=======================
=======================
score : 10
completed : killedst the Egyptian? And Moses feared, and said, Surely this thing
 source : Moses_and_the_Sages__Bible.txt
offset : 4877
=======================
=======================
score : 10
completed : 2:15 Now when Pharaoh heard this thing, he sought to slay Moses. But
 source : Moses_and_the_Sages__Bible.txt
offset : 4880
=======================


please insert your prefix :
moss

*********** runtime : 576 microseconds ***********

=======================
score : 8
completed : perfectly wonderful. She wore a moss-coloured velvet jerkin with
 source : The picture of Dorian Gray.txt
offset : 2974
=======================
=======================
score : 8
completed : perfectly wonderful. She wore a moss-coloured velvet jerkin with
 source : The picture of Dorian Gray.txt
offset : 2974
=======================
=======================
score : 8
completed : perfectly wonderful. She wore a moss-coloured velvet jerkin with
 source : The picture of Dorian Gray.txt
offset : 2974
=======================
=======================
score : 8
completed : perfectly wonderful. She wore a moss-coloured velvet jerkin with
 source : The picture of Dorian Gray.txt
offset : 2974
=======================
=======================
score : 8
completed : perfectly wonderful. She wore a moss-coloured velvet jerkin with
 source : The picture of Dorian Gray.txt
offset : 2974
=======================


please insert your prefix :
cana

*********** runtime : 42 microseconds ***********

=======================
score : 8
completed : Ham, and Japheth: and Ham is the father of Canaan.
 source : Moses_and_the_Sages__Bible.txt
offset : 661
=======================
=======================
score : 8
completed : 9:22 And Ham, the father of Canaan, saw the nakedness of his father,
 source : Moses_and_the_Sages__Bible.txt
offset : 670
=======================
=======================
score : 8
completed : 9:25 And he said, Cursed be Canaan; a servant of servants shall he be
 source : Moses_and_the_Sages__Bible.txt
offset : 681
=======================
=======================
score : 8
completed : 9:26 And he said, Blessed be the LORD God of Shem; and Canaan shall be
 source : Moses_and_the_Sages__Bible.txt
offset : 684
=======================
=======================
score : 8
completed : Shem; and Canaan shall be his servant.
 source : Moses_and_the_Sages__Bible.txt
offset : 688
=======================


please insert your prefix :
salem

*********** runtime : 44 microseconds ***********

=======================
score : 10
completed : 14:18 And Melchizedek king of Salem brought forth bread and wine: and
 source : Moses_and_the_Sages__Bible.txt
offset : 1037
=======================
=======================
score : 10
completed : 10:1 Now it came to pass, when Adonizedec king of Jerusalem had heard
 source : Moses_and_the_Sages__Bible.txt
offset : 19664
=======================
=======================
score : 10
completed : 10:3 Wherefore Adonizedec king of Jerusalem, sent unto Hoham king of
 source : Moses_and_the_Sages__Bible.txt
offset : 19672
=======================
=======================
score : 10
completed : 10:5 Therefore the five kings of the Amorites, the king of Jerusalem,
 source : Moses_and_the_Sages__Bible.txt
offset : 19678
=======================
=======================
score : 10
completed : of the cave, the king of Jerusalem, the king of Hebron, the king of
 source : Moses_and_the_Sages__Bible.txt
offset : 19749
=======================


## Run:
to run it,firstly you need to parse text files to a json file using the python parser in parse lines directory, after that you should put the json file in jsons directory and compile the program using this line :

g++ -o runme AutoCompleteMain.cpp AutoCompleteData.h -ljsoncpp

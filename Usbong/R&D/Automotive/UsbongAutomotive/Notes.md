# Usbong Automotive: Notes

<img src="https://github.com/usbong/documentation/blob/master/Usbong/R%26D/Automotive/UsbongAutomotive/screenshots/UsbongAutomotiveV20210205T1703.gif" width="60%">

## 1) Linux Machine
Execute Command (in Terminal Window): <b>./UsbongAutomotiveLinux</b><br/>
--> <b>location:</b> "output" folder
### 1.1) Problem: "./UsbongAutomotiveLinux: error while loading shared libraries: libglut.so.3: cannot open shared object file: No such file or directory"
<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt-get update</b><br/>
<b>sudo apt-get install freeglut3</b><br/>

#### 1.1.1) Problem: "E: Unmet dependencies. Try 'apt --fix-broken install' with no packages (or specify a solution)."
<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt --fix-broken install</b><br/>
<b>sudo apt-get install freeglut3</b><br/>

### 1.2) Problem: How to execute recording of continuous sequence of screenshots?
<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt-get install byzanz</b><br/>
<b>byzanz-record --duration=6 --x=0 --y=0 --width=600 --height=600 outHalimbawa.gif</b><br/>

#### References:
1.2.1) https://askubuntu.com/questions/4428/how-can-i-record-my-screen;<br/>
last accessed: 20210205T1722<br/>
answer by: fossfreedom, 20170413T1224<br/>

1.2.2) https://askubuntu.com/questions/107726/how-to-create-animated-gif-images-of-a-screencast;<br/>
last accessed: 20210205T1722<br/>
answer by: Bruno Pereira, 20120419T1947<br/>
edited by: Pablo Bianchi, 20190504T0401<br/>

### 1.3) Problem: ./make.sh: line 22: g++: command not found
<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt-get install g++</b><br/>

### 1.4) Problem: compilation terminated.
<b>
/usr/bin/ld: cannot find -lGL<br/>
/usr/bin/ld: cannot find -lGLU<br/>
/usr/bin/ld: cannot find -lglut<br/>
</b>
<br/>
<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt-get install mesa-utils</b><br/>
<b>sudo apt-get install freeglut3-dev</b><br/>

#### References (1.3 and 1.4):
https://askubuntu.com/questions/96087/how-to-install-opengl-glut-libraries;<br/>
last accessed: 20210226<br/>
answered by: A-Sharabiani, 20170719T0335<br/>
edited by: Amir, 20180425T1940

### 1.5) Problem: fatal error: GL/gl.h: No such file or directory

<b>Answer:</b> Execute Commands (in Terminal Window):<br/>
<b>sudo apt-get install aptitude</b><br/>
<b>sudo aptitude install freeglut3-dev</b><br/>

#### Additional Notes: 
If computer asks you if you accept its solution that <b>freeglut3-dev</b> shall NOT be installed due to dependencies, enter "<b>n</b>" to signify "<b>NO</b>". The computer shall then notify you regarding the "downgrade" packages action to resolve the dependencies problem. Enter "<b>Y</b>" to signify "<b>YES</b>".<br/>

#### Reference:
https://askubuntu.com/questions/96087/how-to-install-opengl-glut-libraries/1357334#1357334;<br/>
last accessed: 20210811<br/>
answered by: SYSON, MICHAEL B. as masarapmabuhay, 20210811

## 2) Windows Machine
### 2.1) Problem: When executing UsbongAutomotive.exe, computer notifies you that glut32.dll does not exist
<b>Answer:</b> Execute the following steps:<br/>
2.1.1) Download <b>glut-3.7.6-bin.zip (117 KB)</b> from https://user.xmission.com/~nate/glut.html.<br/>
--> web address last accessed: 20210216<br/>
<br/>
2.1.2) Extract zip file to present directory.<br/>
<br/>
2.1.3) Copy "glut32.dll" from extracted folder.<br/>
<br/>
2.1.4) Paste "glut32.dll" to UsbongAutomotive's WindowsAndLinux output folder.<br/>
--> Reminder: UsbongAutomotive.exe is located in the output folder.<br/>
<br/>
Done! You can now execute UsbongAutomotive.exe!

#### Reference:
2.1.5) https://answers.microsoft.com/en-us/windows/forum/windows_vista-windows_programs/opengl-glut-used-to-work-on-xp-get-glut32dll-not/8858c510-dc6c-4e11-9958-d3cb4a883227<br/>
last accessed: 20210216T0512<br/>
answer by: MattS440, 20100118<br/>

## 3) Human Person
### 3.1) Parts
3.1.1) upper arm;<br/>
3.1.1.1) humerus<br/>
<br/>

3.1.2) lower arm;<br/>
3.1.2.1) radius<br/>
3.1.2.2) ulna<br/>
<br/>

3.1.3) upper leg;<br/>
3.1.3.1) femur<br/>
<br/>

3.1.4) lower leg<br/>
3.1.4.1) fibula<br/>
3.1.4.2) tibia<br/>
<br/>

#### Reference: 
1) https://www.mayoclinic.org/diseases-conditions/broken-arm/multimedia/arm-bones/img-20007018; last accessed: 20201229

### 3.2) Add-on Parts
3.2.1) bone + joint + bone<br/>
--> where: tendon = +<br/>
<br/>
3.2.2) bone + muscle<br/>
--> where: ligament = +<br/>
<br/>
--> This action is as learned working at Marikina Orthopedic Specialty Clinic (MOSC), et cetera

### 3.3) Additional Notes #1
3.3.1) Arthritis: joint pain<br/>
--> Osteoarthritis; where osteo = bone<br/>
<br/>
3.3.2) Ear, Nose, Throat<br/>
--> Sodium Chloride + Benzalkonium Chloride 0.02%<br/>
--> verified: Sodium Chloride as Table Salt + water used for gargling to solve to a certain extent throat pain<br/>
--> This action is as learned living with Japanese family<br/>
<br/>
--> "Benzalkonium chloride is widely used as a preservative in eye-drops, in higher concentrations it is used as an antiseptic and disinfectant."<br/>
--> https://www.sciencedirect.com/topics/immunology-and-microbiology/benzalkonium-chloride;<br/>
--> last accessed: 20211112<br/>
<br/>
### 3.4) Additional Notes #2
3.4.1) Poison causes itch in skin, tongue, et cetera<br/>
--> <b>Example:</b> poison from jellyfish, fugu fish<br/>
--> Select know-how learnable by swimming in Philippine sea<br/>
--> Select know-how learnable by living with Japanese family<br/>

### 3.5) Action Technique
3.5.1) Shotokan Karate<br/>
--> https://www.youtube.com/user/shotokankataman/videos;<br/>
--> last accessed: 20210509<br/>
--> Heian Shodan - Shotokan Karate<br/>
--> Peace Beginner Level<br/>
<br/>
3.5.1.1) 合気道 (あいきどう；aikidou）<br/> 
--> (pinagsamang kaluluwa daan)<br/>
<br/>
3.5.1.2) 平安　（へいあん、初段～五段; heian, shodan ~ godan）<br/>
--> (payapa; patag babae may bubong; simulang nibel ~ ikalimang nibel)<br/>
<br/>
3.5.1.3) 鉄騎初段　（てつ＋き＋しょだん; tetsu + ki + shodan）<br/>
--> bakal na kabayo malaki maaari simulang nibel <br/>
<br/>
3.5.1.4) 抜塞大　（ぬく＋ふさぐ＋おおきい; nuku + fusagu + ookii）<br/>
--> tanggalin baradong malaki<br/>
<br/>
3.5.1.5) 観空大　（みる＋くう・そら＋おおきい; miru + kuu・sora + ookii）<br/>
--> masdan kawalan・kalangitan malaki<br/>
<br/>
・・・<br/>
<br/>

## 4) Paalala:
<b>4.1)</b> 結局、歴史では、戦争が伸びてると、<br/>
Kinalauanan, sa kasaysayan, sa paghaba ng digmaan,<br/>
<br/>
兵士が疲れるし、供給なども切れる・・・<br/>
napapagod ang sundalong mag-aaral, napuputol ang bigay na pagsasaluhan (supply)...<br/>
<br/>
敵がわかれば、ターゲットして、<br/>
Kapag alam na ang kalaban, gawing target,<br/>
<br/> 
優柔不断をせずに、早めに終わりにすること。<br/>
hindi gawin ang walang hintong bait at pag-aakma (flexible), tapusin na habang maaga pa.<br/> 
<br/>
わくわくすることなく、仕事としての決断でね。<br/>
hindi gawin nang may excitement; bilang hanap-buhay pagpasiyahan, hinto.<br/>
<br/>
<b>4.2)</b> うまくできることをして、<br/>
Gawin ang maiging nagagawa,<br/>
<br/>
意味がわからず、うまくできないことを<br/>
hindi maunawaan ang saysay, hindi maiging magawa,<br/>
<br/>
他にして良い。<br/>
Sa magagawa ipagawa, ayos.<br/>
<br/>
<b>4.3)</b>　budol-budol/manloloko/carnapper/cybercriminal/Teroristang Komunista group<br/>
--> Patuloy araw-gabi ang kanilang maling paggamit ng wireless broadcasting technology sa paggawa ng panlolokong ingay at pisikal na pananakit.<br/>
--> Kahit ang Nanay-nayan kong Hapon binabastos.<br/>
<br/>
--> <b>Mungkahing mga Aksyon:</b><br/> 
4.3.1) Matuto ng Maparaang Pagbibilang.<br/>
4.3.2) Gawan ng incident report ang Pulis.<br/>
4.3.3) Puksain ang mga Teroristang Komunista.<br/>
--> Hindi na kailangang makipag-usap sa mga Manloloko.<br/>
--> There is NO COMMUNICATION using Teroristang Komunista's wireless broadcasting technology.<br/>
--> In its stead, increased Noise Pollution with Physical Injury <br/>
<br/>
生き残りながら、がんばって、<br/>
ikinokorinagara, gambatte,<br/>
Habang natitirang nabubuhay, gawin nang lubos ang magagawa,<br/>
<br/>
この犯罪グループを終わりに致しております。<br/>
kono guru-pu wo owarini itashite ormasu.<br/>
ang kriminal na samahang ito, wakasin, ginagawa ko po.<br/>
<br/>
ご協力をお願い申し上げます。<br/>
gokyouryoku wo onegai moushiagemasu.<br/>
Ang inyo pong pinagsamang tulong na lakas, aking may galang na pakiusap.<br/>

#include <string>
#include <iostream>
using namespace std;

void TTS(string input) {

    system("echo Set speech = Wscript.CreateObject(\"SAPI.spVoice\") > temp.vbs"); 
	system("echo Set speech.Voice = speech.GetVoices.Item(1) >> temp.vbs");
	string command = "echo speech.speak \"<pitch middle ='0' />";
	command += input;
	command += "\" >> temp.vbs";
	system(command.c_str());
	system("start temp.vbs");
	//system("del temp.vbs");

}

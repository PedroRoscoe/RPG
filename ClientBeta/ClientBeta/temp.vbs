Set speech = Wscript.CreateObject("SAPI.spVoice") 
Set speech.Voice = speech.GetVoices.Item(1) 
speech.speak "<pitch middle ='0' />Insert Server Code" 

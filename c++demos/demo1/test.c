#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <ApplicationServices.h>

int doneflag = 0;

void SpeechDoneProc (SpeechChannel chan, long refCon)
{
    DisposeSpeechChannel(chan);
    doneflag++;
}

void SpeakThisText(const void *text, long size)
{
    SpeechChannel chan;

    NewSpeechChannel (NULL, &chan);
    SetSpeechInfo(chan, soSpeechDoneCallBack, (void*)&SpeechDoneProc); // we install a callback to dispose the channel when ready
    SpeakText (chan, text, size);
}


int main() {
	SpeakThisText("hello",6);
	while(!doneflag);

	printf("done");

}
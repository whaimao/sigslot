#include <iostream>
#include <string.h>
#include <unistd.h>
#include "sigslot.h"
using namespace sigslot;
class Sender{
	public:
		sigslot::signal2<std::string, int> signalSender;
		void help(){
			signalSender("help", 1);
		}
		void help2(){
			signalSender("help,hahah,just test",2);
		}
	
};
class Recevier:public sigslot::has_slots<>{
	public:
		void onRecevier(std::string message, int type){//参数与Sender 中的signalSender要一致
			if(type == 1){
				std::cout << "I'am help() slot" <<std::endl;
			}else{
				std::cout << "I'm help2() slot" << std::endl;
			}
		}
};
int main(void){
	
	Sender s1;
	Recevier r1;
	s1.signalSender.connect(&r1, &Recevier::onRecevier);
	sleep(3);
	s1.help();
	sleep(3);
	s1.help2();
	sleep(3);
	s1.signalSender.disconnect(&r1);
	return 0;
}
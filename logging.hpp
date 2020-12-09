#pragma once
#include <iostream>
#define log(x) std::cout<<"["<<__FILE__<<"]: "<<__LINE__<<" - "<<x<<std::endl;
#define log_err(x) std::cerr<<"["<<__FILE__<<"]: "<<__LINE__<<" - "<<x<<std::endl;
#include "System.h"

int main(){
  System system = System();
  system.addObject();

  for (uint32_t i = 0; i < 1000; ++i){
    system.update(0.0f);
  }
  
}

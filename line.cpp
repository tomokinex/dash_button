#include <stdlib.h>
void execute(){
    system("curl -X POST https://maker.ifttt.com/trigger/{$event}}/with/key/{$key}");
}
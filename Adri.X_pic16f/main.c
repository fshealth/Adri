#include "system.h"

/*========= Função main ============*/
void main(void)
{
    configura_pic();
    configura_uart();
    atualiza_relogio();
    atualiza_variaveis();
    while(1)
    {
        controle_servo(0);
        if(libera == 1)
        {
            aciona();
        }
    }
}

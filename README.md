# Temporizador de Disparo (One Shot) para Raspberry Pi Pico W

Este projeto implementa um temporizador de disparo (One Shot) utilizando o Raspberry Pi Pico W. O temporizador aciona três LEDs (azul, vermelho e verde) em sequência, com um intervalo de 3 segundos entre o desligamento de cada LED. O sistema utiliza um botão para iniciar o ciclo de LEDs e implementa debounce para garantir um controle de pressionamento adequado.

## Componentes utilizados:

- **Raspberry Pi Pico W**
- **LEDs** conectados aos GPIOs 11, 12, 13 (azul, vermelho e verde, respectivamente)
- **Botão** conectado ao GPIO 5

## Funcionalidade:

- O botão (GPIO 5) inicia a sequência de LEDs quando pressionado.
- Os LEDs (GPIOs 11, 12 e 13) acendem simultaneamente e se apagam em sequência, com um atraso de 3 segundos entre o apagamento de cada um.
- O sistema implementa debounce para garantir que o botão seja lido corretamente e evita múltiplos disparos rápidos.
- O ciclo de LEDs não pode ser reiniciado até que todos os LEDs sejam apagados.

## Como usar:

1. Conecte o Raspberry Pi Pico W com o código carregado em seu ambiente de desenvolvimento.
2. Conecte os LEDs aos GPIOs 11, 12 e 13 para azul, vermelho e verde, respectivamente.
3. Conecte o botão ao GPIO 5.
4. Ao pressionar o botão, os LEDs acendem simultaneamente e se apagam em sequência, com 3 segundos de intervalo entre os apagamentos.

## Requisitos:

- Raspberry Pi Pico W
- Wokwi e BitDogLab para simulação (caso esteja usando para testar)

## Como compilar e carregar:

1. Certifique-se de ter o **Raspberry Pi Pico SDK** configurado corretamente em seu ambiente de desenvolvimento.
2. Compile o código utilizando sua IDE preferida.
3. Carregue o código no Raspberry Pi Pico W.

##

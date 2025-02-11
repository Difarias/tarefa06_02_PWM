
# Tarefa 06/02 - Módulo PWM

## Objetivo
O objetivo desta atividade é projetar um sistema utilizando o módulo PWM do microcontrolador RP2040 para controlar o ângulo de um servomotor. A simulação será realizada no simulador de eletrônica Wokwi (integrado ao vscode), e o comportamento do LED RGB será observado durante a execução do código na placa BitDogLab conectada.

## Requisitos
1. Configurar a GPIO 22 com frequência de PWM de aproximadamente 50Hz (período de 20ms).
2. Definir o ciclo ativo do PWM para 2.400µs (0,12% de duty cycle) para posicionar o servo em 180° e aguardar 5 segundos.
3. Definir o ciclo ativo do PWM para 1.470µs (0,0735% de duty cycle) para posicionar o servo em 90° e aguardar 5 segundos.
4. Definir o ciclo ativo do PWM para 500µs (0,025% de duty cycle) para posicionar o servo em 0° e aguardar 5 segundos.
5. Criar uma rotina para movimentação suave do servo entre 0° e 180° com incremento de ±5µs e atraso de 10ms.
6. Utilizar o LED RGB (GPIO 12) para observar o comportamento da iluminação durante a execução do código.

## Como Rodar o Projeto

### Passo 1: Clonar o Repositório
```bash
git clone https://github.com/Difarias/tarefa06_02_PWM
```

### Passo 2: Acessar a Pasta do Projeto
```bash
cd tarefa06_02_PWM/
code .
```

### Passo 3: Gerar a Pasta Build e Compilar o Projeto
```bash
mkdir build/
cd build/
cmake ..
make
```

### Passo 4: Executar no Wokwi
- Integre o Wokwi ao VSCode e utilize o arquivo `diagram.json` para simular o circuito.
- Observe o comportamento do servo-motor e olhe o terminal com as informações.

### Passo 5: Copiar o .uf2 para a Placa
- Após a compilação, copie o arquivo `.uf2` gerado para a placa Raspberry Pi Pico.
- Observe o comportamento do LED RGB na placa física, identificando a intensidade do led que muda com a angulação do servo-motor.

## Vídeo Demonstração
[![Link do Vídeo](https://img.youtube.com/vi/z2uhRnvfHxM/0.jpg)](https://youtu.be/z2uhRnvfHxM)

## Desenvolvedor

- Desenvolvido por Diêgo Farias de Freitas

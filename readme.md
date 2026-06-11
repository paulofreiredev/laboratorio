# 🔬 Laboratório de Eletrônica

Repositório pessoal utilizado para estudar eletrônica, microcontroladores, Arduino, ESP32, protocolos de comunicação e integração com aplicações externas.

O objetivo não é apenas guardar código, mas também documentar experimentos, erros, descobertas e servir como material de consulta futura.

## Estrutura

```
.
├── app/
│   ├── process/
│   └── serial/
│
├── arduino/
│   ├── codigo/
│   └── design-circuito/
│
└── README.md
```

### `/arduino/codigo`

Contém os códigos executados nos microcontroladores.

Cada pasta representa um projeto ou experimento independente.

### `/arduino/design-circuito`

Contém imagens, esquemas elétricos, fotos da montagem e pinagens utilizadas pelos projetos.

### `/app`

Aplicações executadas no computador para integração com o Arduino/ESP32.

Exemplos:

- visualização gráfica
- comunicação serial
- aplicações em Processing
- programas auxiliares em C

---

# Projetos

## 🔘 btn

Experimento simples utilizando botões digitais.

Objetivos:

- leitura de entradas digitais
- pull-up e pull-down
- debounce
- interação básica com GPIO

Circuito:

```
arduino/design-circuito/btn/
```

---

## 📡 Serial

Exemplo básico de comunicação Serial.

Conceitos:

- Serial.begin()
- Serial.print()
- monitor serial
- comunicação PC ↔ Arduino

---

## 📥 Serial_receive

Recebimento de dados enviados pela Serial.

Conceitos:

- leitura de caracteres
- leitura de strings
- interpretação de comandos

---

## 🖥️ MCUServerSerial

Experimento de comunicação entre uma aplicação externa e o microcontrolador utilizando porta serial.

Objetivos:

- protocolo simples
- troca de mensagens
- integração com aplicações desktop

---

## 📶 Mqtt

Projeto de comunicação MQTT utilizando ESP32.

Conceitos estudados:

- Wi-Fi
- MQTT
- Pub/Sub
- IoT
- Broker MQTT

Este projeto utiliza credenciais armazenadas em `secrets.h`.

---

## 📡 Sonar

Projeto utilizando sensor ultrassônico.

Objetivos:

- medir distância
- calcular tempo de propagação
- visualizar dados

Existe também uma aplicação em:

```
app/process/Sonar/
```

que faz a representação gráfica das leituras.

---

## 🐍 snake-game

Experimento de desenvolvimento de um jogo em hardware utilizando Arduino.

Objetivo:

- estudar manipulação de display
- lógica de jogo
- atualização de tela
- controle por botões

---

# Credenciais (secrets.h)

Alguns projetos utilizam Wi-Fi e outras credenciais que **não devem ser enviadas para o GitHub**.

Crie o arquivo:

```
arduino/codigo/secrets.h
```

Exemplo:

```cpp
#ifndef SECRETS_H
#define SECRETS_H

#define WIFI_SSID "MeuWifi"
#define WIFI_PASSWORD "MinhaSenha"

#define MQTT_SERVER "192.168.0.10"
#define MQTT_PORT 1883

#define MQTT_USERNAME "usuario"
#define MQTT_PASSWORD "senha"

#endif
```

Nos projetos basta incluir:

```cpp
#include "../secrets.h"
```

> O arquivo `secrets.h` deve estar listado no `.gitignore`.

Exemplo:

```
arduino/codigo/secrets.h
```

Também é recomendado manter um arquivo de exemplo:

```
arduino/codigo/secrets.example.h
```

com valores fictícios para facilitar a configuração em outra máquina.

---

# Objetivos de estudo

Este laboratório é utilizado para estudar:

- Eletrônica digital
- Eletrônica básica
- Arduino
- ESP32
- GPIO
- PWM
- Timers
- Interrupções
- UART
- SPI
- I2C
- MQTT
- Comunicação Serial
- Sensores
- Displays
- Processing
- Integração PC ↔ Microcontrolador

---

# Filosofia

Este repositório funciona como um caderno de laboratório.

Cada projeto pode conter:

- código-fonte
- esquema elétrico
- foto da montagem
- observações
- problemas encontrados
- soluções adotadas
- referências utilizadas
# Projeto de Prevenção de Acidentes Causados por Enchentes

## 💡 Sobre o Projeto

Inspirados pelos recentes acontecimentos no estado de São Paulo, onde diversos municípios foram afetados por enchentes, desenvolvemos esta aplicação com o objetivo de ajudar na prevenção de desastres naturais.

Utilizando o microcontrolador **ESP32**, nosso sistema coleta dados meteorológicos do local onde o usuário se encontra, permitindo prever, com base nas condições climáticas, se há risco de enchente no dia. A ideia é fornecer um alerta antecipado para que as pessoas possam se preparar e evitar riscos.

---

## 🛠️ Extensões Necessárias no VSCode

Para executar e simular este projeto, é necessário instalar as seguintes extensões no Visual Studio Code:

- [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
- [Wokwi Simulator](https://marketplace.visualstudio.com/items?itemName=wang-yan.wokwi)

---

## ⚙️ Preparação do Ambiente

1. Iniciar o PlatformIO no terminal com o comando:

   ```bash
   pio run

2. Acessar o Node-RED no navegador usando o endereço:

   ```cpp
   http://172.208.54.189:1880
   
## 🚀 Inicialização do Projeto

1. Abra o arquivo **diagram.json** para visualizar o diagrama do Wokwi.
2. Caso ocorra algum erro na simulação, pressione **F1** no VSCode e procure por:

   ```makefile
   Wokwi: Start Simulator

## 🔗 Integração com o Node-RED

Se tudo estiver corretamente configurado, ao acessar o Node-RED, você verá um objeto com os seguintes dados:

   ```json
   {
  "ID": "quantumLeap",
  "Sensor": "Meu_ESP32",
  "IP": "10.13.37.2",
  "MAC": "24:0A:C4:00:01:10",
  "Umidade": 40
}

Esses dados representam as informações enviadas pelo sensor do ESP32 para o fluxo do Node-RED, que pode ser usado para análise e tomada de decisão sobre riscos de enchente.



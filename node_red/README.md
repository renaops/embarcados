# Sistema de monitoramento de água com ESP/NodeMCU, MQTT e Node-RED

Este projeto utiliza um módulo ESP/NodeMCU para se comunicar via MQTT com um servidor MQTT (como o Node-RED). O Node-RED pode ser configurado para receber os dados do ESP/NodeMCU, processá-los e fornecer uma interface web.

## Requisitos

- Módulo ESP8266 (NodeMCU)
- Conexão Wi-Fi para o ESP8266
- MQTT Broker (pode ser configurado usando Node-RED)
- Node-RED para processamento dos dados e interface web
- Capacidade de acessar o servidor Node-RED a partir de dispositivos conectados à mesma rede Wi-Fi

## Configuração

### ESP/NodeMCU

1. Configure as informações de rede Wi-Fi no código do NodeMCU.
2. Configure o endereço do servidor MQTT no código do NodeMCU.
3. Carregue o código para o NodeMCU usando a Arduino IDE.

### Node-RED

1. Crie um fluxo no Node-RED para receber os dados MQTT do ESP/NodeMCU e processá-los conforme necessário.
2. Configure um nó MQTT no Node-RED para se conectar ao mesmo servidor MQTT usado pelo ESP/NodeMCU.

## Uso

1. Após carregar o código no NodeMCU, o dispositivo se conectará à rede Wi-Fi e ao servidor MQTT.
2. No Node-RED, configure um fluxo para receber dados MQTT do tópico "devices/agua" e processe conforme necessário.
3. No Node-RED, forneça uma interface web para que os usuários acompanhem o nível da água.

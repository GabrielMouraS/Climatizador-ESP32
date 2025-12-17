# ❄️ Climatizador IoT - ESP32 Controller

> Sistema de automação para climatizadores e ventiladores antigos, transformando equipamentos legados em dispositivos inteligentes (IoT) controlados via Wi-Fi com interface Web embarcada.

![C++](https://img.shields.io/badge/C%2B%2B-Embedded-blue)
![ESP32](https://img.shields.io/badge/Hardware-ESP32-red)
![IoT](https://img.shields.io/badge/IoT-Smart%20Home-green)
![Status](https://img.shields.io/badge/Status-Funcional-brightgreen)

---

## 📹 Demonstração
Veja o sistema em funcionamento: conexão automática via Portal Cativo e acionamento dos relés em tempo real.
https://github.com/user-attachments/assets/28ec968b-28f1-4c9a-8227-6ff9c7082257
*Clique na imagem acima para assistir ao vídeo de demonstração.*

---

## 🎯 Objetivo
Substituir o painel de controle físico (botões mecânicos) de um climatizador por um microcontrolador **ESP32**, permitindo o controle total (Bomba, Velocidade, Oscilação) através de qualquer smartphone, sem necessidade de aplicativos externos.

O sistema opera em modo **Offline (SoftAP)**, criando sua própria rede Wi-Fi independente.

---

## ⚙️ Diferenciais Técnicos

### 1. Portal Cativo (DNS Server) 📲
O principal destaque de engenharia deste projeto. Ao conectar no Wi-Fi do dispositivo, o sistema:
* Intercepta requisições DNS (porta 53).
* Redireciona qualquer endereço para o IP do ESP32.
* **Resultado:** A interface de controle abre automaticamente no celular (semelhante a login de Wi-Fi de aeroporto), eliminando a necessidade de digitar IPs manualmente.

### 2. Interface Web Embarcada (PROGMEM) 🌐
* O servidor web roda dentro do ESP32 (Porta 80).
* Todo o código HTML/CSS é armazenado na memória flash do chip, garantindo resposta rápida e dispensando conexão com internet externa.

### 3. Controle de Hardware (6 Canais) ⚡
* Gerenciamento de 6 relés com lógica invertida (padrão de módulos de mercado), permitindo controle granular das funções do aparelho.

---

## 🔌 Pinagem (Hardware)
Mapeamento das conexões GPIO do ESP32 para o módulo de relés:

| Componente Controlado | Função | GPIO (ESP32) |
| :--- | :--- | :---: |
| **Relé 1** | 💧 Bomba de Água / Umidificar | `25` |
| **Relé 2** | 💨 Velocidade Baixa | `26` |
| **Relé 3** | 💨 Velocidade Média | `27` |
| **Relé 4** | 💨 Velocidade Alta | `32` |
| **Relé 5** | 🔄 Oscilar (Swing) | `14` |
| **Relé 6** | ❄️ Extra / Ionizador | `33` |

---

## 🚀 Como Utilizar

1. **Hardware:** Alimente o ESP32 e conecte os pinos aos relés conforme a tabela acima.
2. **Conexão:**
   * No celular ou PC, procure a rede Wi-Fi: **`Climatizador`**.
   * Senha: **`12345678`**.
3. **Acesso:**
   * Aguarde o pop-up de "Fazer login na rede" (Portal Cativo).
   * Caso não abra automaticamente, acesse `http://192.168.4.1` no navegador.
4. **Operação:** Utilize os botões na tela para ligar/desligar cada função.

---

## 🛠️ Tecnologias Utilizadas
* **Hardware:** ESP32 DevKit V1.
* **Linguagem:** C++ (Arduino Framework).
* **Network Stack:** `WiFi.h` (SoftAP), `DNSServer.h` (Captive Portal), `WebServer.h`.

---
**Desenvolvido por Gabriel Moura**

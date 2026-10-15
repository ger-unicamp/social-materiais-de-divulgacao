# 🏎️ Seguidor de Linha Colorida

Este repositório contém a lógica de um robô seguidor de linha que faz mais do que só seguir uma trilha: ele ajusta a própria velocidade dinamicamente de acordo com marcadores de cor no chão.

## 📂 O Código
Toda a lógica em C++ está no arquivo `seguidor_de_cor.cpp`, localizado nesta mesma pasta. É só abrir na IDE do Arduino, compilar e subir para o seu ESP32.

## 🛣️ Como funciona a direção?
O robô usa sensores para rastrear uma linha preta em um fundo claro. A lógica é simples e direta:
* **Sensor esquerdo na linha:** O robô corrige a rota virando para a esquerda.
* **Sensor direito na linha:** O robô corrige virando para a direita.
* **Nenhum na linha:** Ele segue reto até reencontrar o trajeto.

## 🚥 Checkpoints de Cor (Velocidade)
A grande sacada desse projeto é o uso dos sensores RGB. Quando o robô passa por cores específicas na pista, ele altera o PWM dos motores na mesma hora:

* 🔴 **Vermelho (30% da velocidade):** Modo reduzido. Ideal colocar antes de curvas muito fechadas para o robô não "passar direto" e perder a linha.
* 🟡 **Amarelo (60% da velocidade):** Velocidade de cruzeiro. A rotação padrão para manter a estabilidade no trajeto geral.
* 🔵 **Azul (100% da velocidade):** Boost máximo! Libera 100% da potência dos motores. Perfeito para colocar no início de grandes retas e baixar o tempo da volta.

## 🛠️ Como montar e testar
1. **A Pista:** Use fita isolante preta no chão (de preferência um piso claro ou branco). Faça um circuito com retas e curvas variadas.
2. **As Tags:** Recorte pedaços de papel, cartolina ou EVA colorido (Vermelho, Amarelo e Azul) e posicione pelo trajeto.
3. **Ajuste Fino:** Dependendo da iluminação da sua sala, pode ser necessário abrir o `seguidor_de_cor.cpp` e ajustar levemente os multiplicadores na função `atualizarVelocidade` para ele ler as cores com perfeição.
4. **Bora testar:** Ligue a alimentação, coloque o chassi na pista e veja o sistema funcionar na prática.

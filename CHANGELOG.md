# Changelog

Todas as alterações notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Versionamento Semântico](https://semver.org/lang/pt-BR/spec/v2.0.0.html).

## [0.5.1] - 2023-08-31

### Corrigido

- Corrige declaração da dependência com caminho relativo no platformio.ini do exemplo com sensor LV53L0X.

## [0.5.0] - 2023-08-23

### Adicionado

- Exemplo com sensor de distância baseado em laser VL53L0X.

### Corrigido

- Correção de bug que causava reset do dispositivo: falha no uso do locks da fila de medições.
- Correção de problema na lógica dos loops de medição e envio. Fazia-se indesejadamente uma compensação na frequência do loop, provocando iterações em sequência após um atraso grande.

### Alterado

- Melhoria no debug dos projetos de exemplo adicionando filtro para decodificar endereços de erros em tempo de execução.
- Melhoria da medida de distância no exemplo do sensor HC-SR04, fazendo uma média de medidas.
- Melhoria no controle do envio de medições. Como agora o software consegue lidar com sequências de mensagens imediatamente seguidas, o loop envia todas as medições até "quase" zerar a fila. Garante menor latência e evita overflow.
- Métodos para configurar período de medição e envio foram modificados para receberem a frequência ao invés do período.

## [0.4.0] - 2023-08-12

### Adicionado

- Tomada de medições e envio feito de forma assíncrona e com frequência de amostragem e envio bem definidas. Agora o envio não causa um atraso nas medições.
- Diversas otimizações para melhoria da taxa de amostragem.
- Adicionou-se este CHANGELOG.

### Corrigido

- Correção de problema no envio de grandes lotes de medições, que precisam ser divididos em mais de um pacote.

### Alterado

- Melhoria na atualização de status do dispositivo: agora são enviadas atualizações por MDNs quando mudanças ocorrem na conexão com o desktop, assim não é necessário esperar a atualização periódica para ver a disponibilidade do dispositivo atualizada.
- Melhoria nos logs do dispositivo enviados pela Serial.
- Alteração de nomes e propriedades acessíveis para facilitar uso da lib. Board foi transformado em Device e alguns métodos foram alterados.

## [0.3.2] - 2023-08-01

Primeira versão lançada, após ajustes. Transforma o projeto preexistente de um dispositivo na biblioteca propriamente dita, com exemplos que incluem o dispositivo anteriormente desenvolvido.

### Adicionado

- Biblioteca FTRLab
- Exemplo de dispositivo "Física Básica", contendo por enquanto um sensor de distância HC-SR04.
- Exemplo de dispositivo "ESP32 Built-in", utilizando apenas sensores de temperatura da CPU e de Efeito Hall embutidos no ESP32. Ambos com o único objetivo de servir como um exemplo fácil de testar sem hardware adicional.

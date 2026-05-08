# Changelog

Todas as alterações notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Versionamento Semântico](https://semver.org/lang/pt-BR/spec/v2.0.0.html).

## [Não Lançado]

### Adicionado

- Implementa testes unitários no host: alguns simples apenas testando os mocks, outros testando métodos e funções. Cobertura de testes de 45.4% , em linhas de código, e 69.7% , em funções.
- Cria fluxo de integração contínua com testes em host (apenas testes unitários sem hardware)
- Adiciona badges para visualizar estado do pipeline e da cobertura de testes no README.
- Scripts adicionados à configuração do projeto para facilitar a utilização das ferramentas localmente.
  - Script para geração do relatório de cobertura de testes.
  - Script para teste do pipeline de CI localmente.

### Corrigido

- Através dos testes unitários (no host) foi resolvido um bug "invisível" através de testes em corner case: device.sendMeasurementsBatch() falhava com fila de medições vazia, o que a princípio não ocorre em produção, mas a solução deixa o código mais robusto.

### Alterado

- Princípios SOLID.
- Pattern Singleton: Instância única do `Device` garantida.
- Pattern Builder: Criação do dispositivo com injeção das dependência por métodos setters. DeviceBuilder orquestra a criação.
- Pattern Adapter (ou Strategy): As classes dependentes de hardware são feitas com implementação de interfaces bem definidas.
- Simplifica o build dos exmeplos com a biblioteca local em desenvolvimento: cria um ambiente próprio (esp32dev_debug), utilizado a biblioteca local por meio de link simbólico.
- Resolvida a barreira de encapsular a dependência Preferences, removendo a necessidade de fazer a instância no código dos exemplos.

## [0.5.2] - 2023-11-06

### Adicionado

- Adicionou-se doc-strings para os elementos principais da biblioteca.

### Melhorado

- Melhoria nos logs relacionados à sincronização de tempo do dispositivo.

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

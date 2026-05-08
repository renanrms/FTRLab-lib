<a href="https://registry.platformio.org/libraries/renanrms/FTRLab"><img src="https://badges.registry.platformio.org/packages/renanrms/library/FTRLab.svg" alt="PlatformIO Registry" /></a>
<a href="https://github.com/renanrms/FTRLab-lib/actions/workflows/ci.yml"><img src="https://github.com/renanrms/FTRLab-lib/actions/workflows/ci.yml/badge.svg" alt="CI" /></a>
<a href="https://codecov.io/gh/renanrms/FTRLab-lib"><img src="https://codecov.io/gh/renanrms/FTRLab-lib/graph/badge.svg" alt="Coverage" /></a>

# Biblioteca FTRLab

Biblioteca para programação de dispositivos de aquisição de dados em experimentos didáticos que se integram à aplicação [FTRLab desktop](https://github.com/renanrms/FTRLab-desktop). O propósito da Lib é cuidar das tarefas envolvidas por debaixo dos panos, para que o utilizador desenvolva apenas o código específico de medição de cada sensor, ou inclua um sensor previamente implementado.

Habilita comunicação por Wi-Fi, sincronização de tempo, descoberta do dispositivo em uma rede, perfilamento e envio de medições, geração de mensagens de log, e outras funcionalidades automaticamente.

Atualmente funcional para o microcontrolador ESP32.

## Primeiros passos

### Construção de um dispositivo FTRLab

Para criar um dispositivo será necessário montar um protótipo com ESP32 e algum sensor de interesse, e programar um firmware simples para leitura dos sensores importando a biblioteca. Ver [exemplos](#exemplos).

Recomendamos fortemente utilizar a [PlatformIO IDE](#plataformio), como extensão do VScode, para desenvolvimento, compilação e upload do firmware para o dispositivo.

### Exemplos

Veja a [pasta de exemplos](https://github.com/renanrms/FTRLab-lib/tree/main/examples). Cada subpasta contém um exemplo diferente, com um arquivo `platformio.ini`, que torna o diretório um projeto de firmware PlatformIO. Assim você pode abrir a pasta no VScode e utilizar os botões da interface para fazer upload e visualização da saída no serial monitor, ou utilizar a ferramenta CLI.

Perceba que em cada exemplo, a biblioteca é incluída sem especificar uma versão no arquivo `platformio.ini`. Para programar um firmware prefira indicar a versão da lib como recomendado na [seção sobre instalação](https://registry.platformio.org/libraries/renanrms/FTRLab/installation).

## PlatformIO

### Informações gerais

Para utilizar PlatformIO como extensão do VSCode veja a [documentação do PlatformIO](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation). Ela mostra passo a passo como instalar e utilizar a interface para fazer o upload do firmware. Após a instalação do [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/index.html#piocore), para ser capaz de fazer upload dos exemplos para as placas, verifique ainda a página [udev-rules](https://docs.platformio.org/en/latest/core/installation/udev-rules.html).

Também será útil [instalar os comandos Shell](https://docs.platformio.org/en/latest/core/installation/shell-commands.html), para facilitar build e upload via linha de comando. Feito isto, navegue até uma pasta que contém um projeto de firmware PlatformIO (como um dos exemplos) e execute o comando:

```shell
pio run --target upload
```

## Limpeza da memória flash

Um dispositivo com firmware do FTRLab utiliza a memória flash do microcontrolador para armazenar alguns dados de forma persistente, como credenciais de redes conectadas previamente. Estes dados permanecem na memória mesmo após fazer upload de um novo firmware, o que em geral não causa nenhum problema. Mas se for necessário apagar os dados por garantia ou por alguma alteração no formato dos dados salvos, é necessário apagar a memória flash (e o firmware consequentemente).

Para isso são usadas as ferramentas da espressif. Para instalá-las, certifique-se de ter python e pip instalados e depois use os comandos:

```shell
pip install esptool
pip install setuptools
```

Depois, para zerar a memória efetivamente, pressione continuamente o botão BOOT da placa e rode o comando:

```shell
python -m esptool --chip esp32 erase_flash
```

## Desenvolvimento da Lib

Parar verificar o funcionamento de mudanças implementadas na lib, é recomendado
fazer a compilação e upload de um firmware de exemplo com a biblioteca local em
um dispositivo físico. Neste caso a instalação da CLI do Platformio será essencial.

Para fins de demonstração, o comando para utilizar o exemplo `distance-ultrasound` será:

```shell
pio run -d examples/distance-ultrasound/ --target upload -e esp32dev_debug
```

Para monitorar a interface serial do dispositivo (precisa ser na pasta):

```shell
pio device monitor
```

## Testes automatizados

Para rodar os testes unitários localmente (não requer hardware):

```shell
pio test -e native
```

Para rodar os testes de integração no hardware (requer ESP32 conectado):

```shell
pio test -e esp32dev
```

### Cobertura de testes

O relatório é gerado pela ferramenta [gcovr](https://gcovr.com). Instale-a no ambiente virtual do PlatformIO antes do primeiro uso:

```shell
~/.platformio/penv/bin/pip install gcovr
```

Para gerar o relatório, execute os testes e em seguida o target `coverage`:

```shell
pio test
pio run -t coverage
```

O relatório HTML será gerado em `coverage/index.html`. Abra-o no navegador para visualizar a cobertura por arquivo e por linha do código-fonte:

```shell
xdg-open coverage/index.html
```

## Pipeline local de CI

O pipeline de CI usa [GitHub Actions](https://github.com/renanrms/FTRLab-lib/actions). Para rodá-lo localmente antes de subir, instale o [act](https://nektosact.com) — ele simula o runner do GitHub usando Docker:

```shell
curl -s https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash
```

Na primeira execução, configure a imagem padrão (Medium é suficiente):

```shell
mkdir -p ~/.config/act
echo '-P ubuntu-latest=catthehacker/ubuntu:act-latest' > ~/.config/act/actrc
```

Certifique-se de que seu usuário tem permissão para usar o Docker:

```shell
sudo usermod -aG docker $USER
# feche e reabra a sessão para o grupo ter efeito
```

Com tudo configurado, rode o pipeline completo com:

```shell
pio run -t ci
```

Ou diretamente via `act` para rodar jobs específicos:

```shell
act push --job test-host
act push --job build-examples
```

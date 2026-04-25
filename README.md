<a href="https://registry.platformio.org/libraries/renanrms/FTRLab"><img src="https://badges.registry.platformio.org/packages/renanrms/library/FTRLab.svg" alt="PlatformIO Registry" /></a>
<a href="https://github.com/renanrms/FTRLab-lib/actions/workflows/ci.yml"><img src="https://github.com/renanrms/FTRLab-lib/actions/workflows/ci.yml/badge.svg" alt="CI" /></a>

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
pio run -d examples/distance-ultrasound/ --target upload -e esp32dev_local_lib
```

Para monitorar a interface serial do dispositivo (precisa ser na pasta):

```shell
pio device monitor
```

## Testes automatizados

    ✅ Testes nativos: pio test -e native
    ✅ Hardware ESP32: pio test -e esp32dev (requer hardware)

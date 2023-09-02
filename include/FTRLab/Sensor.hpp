#ifndef FTRLAB_SENSOR_H
#define FTRLAB_SENSOR_H "FTRLAB_SENSOR_H"

/**
 * Classe abstrata Sensor
 *
 * Para implementar um sensor deve ser criada uma classe filha desta, fornecendo
 * um valor para a propriedade quantity e uma implementação para o método
 * takeMeasure.
 *
 * Para instruções mais detalhadas veja exemplos da biblioteca em:
 * https://registry.platformio.org/libraries/renanrms/FTRLab/examples
 */
class Sensor
{
public:
  /**
   * Chave para uma grandeza reconhecida pelo software desktop.
   *
   * Caso não seja reconhecida, a chave será utilizada como nome da grandeza,
   * porém a unidade será desconhecida.
   *
   * A lista de grandezas reconhecidas pelo software pode ser obtida em:
   * https://github.com/renanrms/FTRLab-desktop/blob/main/src/renderer/src/constants/quantities.ts
   */
  String quantity;
  /**
   * Informação adicional sobre o sensor. (não utilizada até o momento)
   */
  String method;

  /**
   * Método para tomada de uma medida com o sensor. Deve sem implementado na
   * classe filha.
   *
   * Retorna o valor da medição como String.
   */
  virtual String takeMeasure() = 0;

private:
};

#endif

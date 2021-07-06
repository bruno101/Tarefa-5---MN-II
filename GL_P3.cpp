#include "GL_P3.h"
#include <iostream>

GL_P3::GL_P3(Funcao* integrando, double a, double b, int particao_ou_precisao, int numero_de_particoes, double precisao) {

  this->integrando = integrando;
  this->a = a;
  this->b = b;
  this->particao_ou_precisao = particao_ou_precisao;
  this->numero_de_particoes = numero_de_particoes;
  this->precisao = precisao;

}

double GL_P3::integracao(Funcao *fun, double a1, double b1) {

  double h = (b1-a1)/2;
  double alpha_1 = -sqrt(3.0/5.0);
  double alpha_2 = 0.0;
  double alpha_3 = sqrt(3.0/5.0);
  double x_alpha_1 = (b1+a1)/2 + h*alpha_1;
  double x_alpha_2 = (b1+a1)/2 + h*alpha_2;
  double x_alpha_3 = (b1+a1)/2 + h*alpha_3;
  double w1 = 5.0/9.0;
  double w2 = 8.0/9.0;
  double w3 = 5.0/9.0;
  return h*(w1*(fun->f(x_alpha_1))+w2*(fun->f(x_alpha_2))+w3*(fun->f(x_alpha_3)));
  
}

double GL_P3::integrarP(int n) {

  double step = (b-a)/n;

  double integral = 0;

  for (int i = 0; i < n; i++) {
    integral += integracao(integrando, a+step*i, a+step*(i+1));
  }

  return integral;

}

double GL_P3::integrar () {

  double integral = 0;

  if (particao_ou_precisao == 1) {

    integral = integrarP(numero_de_particoes);

  } else {

    double n = 1;
    double oldIntegral;

    while (1) {

      integral = integrarP(n);
      
      if (n == 1) {

        oldIntegral = integral;
        n*=2;
        continue;

      } else {

        if ( abs( (integral-oldIntegral)/integral ) < precisao) {
          std::cout << "O número de partições usado foi N = " << n << "\n";
          break;
        }

        n*=2;
        oldIntegral = integral;

      }

    }


  }

  return integral;

}
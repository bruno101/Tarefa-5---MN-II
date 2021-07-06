#include "GL_P4.h"
#include <iostream>

GL_P4::GL_P4(Funcao* integrando, double a, double b, int particao_ou_precisao, int numero_de_particoes, double precisao) {

  this->integrando = integrando;
  this->a = a;
  this->b = b;
  this->particao_ou_precisao = particao_ou_precisao;
  this->numero_de_particoes = numero_de_particoes;
  this->precisao = precisao;

}

double GL_P4::integracao(Funcao *fun, double a1, double b1) {

  double h = (b1-a1)/2;
  double alpha_1 = -sqrt(3.0/7.0+2.0*sqrt(6.0/5.0)/7.0);
  double alpha_2 = -sqrt(3.0/7.0-2.0*sqrt(6.0/5.0)/7.0);
  double alpha_3 = sqrt(3.0/7.0-2.0*sqrt(6.0/5.0)/7.0);
  double alpha_4 = sqrt(3.0/7.0+2.0*sqrt(6.0/5.0)/7.0);
  double x_alpha_1 = (b1+a1)/2 + h*alpha_1;
  double x_alpha_2 = (b1+a1)/2 + h*alpha_2;
  double x_alpha_3 = (b1+a1)/2 + h*alpha_3;
  double x_alpha_4 = (b1+a1)/2 + h*alpha_4;
  double w1 = (18.0-sqrt(30.0))/36;
  double w2 = (18.0+sqrt(30.0))/36;
  double w3 = (18.0+sqrt(30.0))/36;
  double w4 = (18.0-sqrt(30.0))/36;
  return h*(w1*(fun->f(x_alpha_1))+w2*(fun->f(x_alpha_2))+w3*(fun->f(x_alpha_3))+w4*(fun->f(x_alpha_4)));
  
}

double GL_P4::integrarP(int n) {

  double step = (b-a)/n;

  double integral = 0;

  for (int i = 0; i < n; i++) {
    integral += integracao(integrando, a+step*i, a+step*(i+1));
  }

  return integral;

}

double GL_P4::integrar () {

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
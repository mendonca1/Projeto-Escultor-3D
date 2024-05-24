#include "sculptor.hpp" 

int main() {
      // Cria uma instância da classe Sculptor
      Sculptor sculptor(10, 10, 10);

      // Define a cor vermelha 
      sculptor.setColor(1.0, 0.0, 0.0, 1.0); // Vermelho
      
      // Desenha um voxel na posição (5, 5, 5)
      sculptor.putVoxel(5, 5, 5);

      // Define a cor para verde 
      sculptor.setColor(0.0, 1.0, 0.0, 1.0); // Verde
      
      // Desenha uma caixa de (1,1,1) a (3,3,3)
      sculptor.putBox(1, 3, 1, 3, 1, 3); 

      // Define a cor para azul
      sculptor.setColor(0.0, 0.0, 1.0, 1.0); // Azul
      
      // Desenha uma esfera com raio 3 centrada em (5,5,5)
      sculptor.putSphere(5, 5, 5, 3); 

      // Define a cor para amarelo
      sculptor.setColor(1.0, 1.0, 0.0, 1.0); // Amarelo

      // Desenha um elipsoide centrado em (5,5,5)
      sculptor.putEllipsoid(5, 5, 5, 3, 2, 1); 

      // Define a cor para verde 
      sculptor.setColor(0.0, 1.0, 0.0, 1.0); // Verde

      // Desenha uma caixa de (1,1,1) a (3,3,3)
      sculptor.putBox(1, 3, 1, 3, 1, 3); 

      // Define a cor para azul 
      sculptor.setColor(0.0, 0.0, 1.0, 1.0); // Azul

       // Desenha uma esfera com raio 3 centrada em (5,5,5)
      sculptor.putSphere(5, 5, 5, 3);

      // Define a cor para amarelo 
      sculptor.setColor(1.0, 1.0, 0.0, 1.0); // Amarelo

      // Desenha um elipsoide centrado em (5,5,5)
      sculptor.putEllipsoid(5, 5, 5, 3, 2, 1); 

      // Salva a matriz 3D em um arquivo OFF
      sculptor.writeOFF("output.off");

      return 0;
  }
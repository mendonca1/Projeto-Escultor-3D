#include <iostream>
#ifndef SCULPTOR_HPP
#define SCULPTOR_HPP
/**
 * @file Sculptor.h
 * @brief Define a classe Sculptor e o struct Voxel.
 */

/**
 * @brief Representa um voxel.
 */
  struct Voxel {
    float r; // Cores
    float g;
    float b; 
    float a; // Trasnparencia
    bool show; // Incluido ou nao
  };
/**
 * @brief A classe Sculptor permite criar esculturas em 3D.
 */
  class Sculptor {
  private:
    Voxel ***v; // 3D matrix
    int nx,ny,nz; // Dimensions
    float r,g,b,a; // Current drawing color
  public:
/**
 * @brief Construtor da classe Sculptor.
 * @param nx Dimensão x da matriz 3D.
 * @param ny Dimensão y da matriz 3D.
 * @param nz Dimensão z da matriz 3D.
 */
    Sculptor(int _nx, int _ny, int _nz);

  /**
  * @brief Destrutor da classe Sculptor.
  */
    ~Sculptor();
    /**
     * @brief Define a cor atual do escultor.
     * @param r Valor da componente vermelha.
     * @param g Valor da componente verde.
     * @param b Valor da componente azul.
     * @param a Valor da opacidade.
     */
    void setColor(float r, float g, float b, float a);
    /**
     * @brief Ativa o voxel na posição (x, y, z).
     * @param x Coordenada x.
     * @param y Coordenada y.
     * @param z Coordenada z.D
     */
    void putVoxel(int x, int y, int z);
    /**
    * @brief Desativa o voxel na posição (x, y, z).
    * @param x Coordenada x.
    * @param y Coordenada y.
    * @param z Coordenada z.
    */
    void cutVoxel(int x, int y, int z);
    /**
     * @brief Grava a escultura em um arquivo OFF.
     * @param filename Nome do arquivo.
     */
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void writeOFF(const char* filename);
  };

  #endif // SCULPTOR_HPP
   
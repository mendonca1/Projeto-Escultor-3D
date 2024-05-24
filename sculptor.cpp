#include <fstream>
#include "sculptor.hpp"
#include <cmath>
#include <iostream>

// Implementação do construtor da classe Sculptor

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  // Inicializa as dimensões da matriz 3D
  nx = _nx;
  ny = _ny;
  nz = _nz;

  // Aloca memória para a matriz 3D
  v = new Voxel **[nx];
  for (int i = 0; i < nx; i++) {
    v[i] = new Voxel *[ny];
    for (int j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz];
    }
  }
}
// Implementação do destrutor da classe Sculptor
Sculptor::~Sculptor() {
  // Verifica se a matriz não é nula
  if (v != nullptr) {
    // Libera a memória alocada para cada plano xy
    for (int i = 0; i < nx; i++) {
      // Libera a memória alocada para cada linha y
      for (int j = 0; j < ny; j++) {
        delete[] v[i][j];
      }
      // Libera a memória alocada para a linha y
      delete[] v[i];
    }
    // Libera a memória alocada para o plano xy
    delete[] v;
  }
}
// Implementação do método setColor
void Sculptor::setColor(float r, float g, float b, float a) {
  // Define os valores de cor e transparência
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}
// Implementação do método putVoxel
void Sculptor::putVoxel(int x, int y, int z) {
  // Verifica se as coordenadas estão dentro dos limites da matriz 3D
  if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
    // Define o voxel na posição especificada com a cor atual
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    v[x][y][z].show = true;
  }
}
// Remove um voxel
void Sculptor::cutVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false;
    }
}
// Implementação do método writeOFF
void Sculptor::writeOFF(const char *filename) {
  // Abre o arquivo para escrita
  std::ofstream outfile(filename);

  if (!outfile.is_open()) {
    std::cerr << "Erro ao abrir o arquivo " << filename << " para escrita."
              << std::endl;
    return;
  }

  // Contadores de vértices e faces
  int numVertices = 8;
  int numFaces = 6;

  // Conta o número de voxels para determinar o número de vértices e faces
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          numVertices += 8; // Cada voxel tem 8 vértices
          numFaces += 6;    // Cada voxel tem 6 faces
        }
      }
    }
  }

  // Escreve o cabeçalho do arquivo OFF
  outfile << "OFF" << std::endl;
  outfile << "8 6 0" << std::endl;

  // Escreve as coordenadas dos vértices
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          outfile << i - 4.5 << " " << j - 4.5 << " " << k - 4.5 << std::endl;
          outfile << i - 4.5 << " " << j + 5.5 << " " << k - 4.5 << std::endl;
          outfile << i + 5.5 << " " << j + 5.5 << " " << k - 4.5 << std::endl;
          outfile << i + 5.5 << " " << j - 4.5 << " " << k - 4.5 << std::endl;
          outfile << i - 4.5 << " " << j - 4.5 << " " << k + 5.5 << std::endl;
          outfile << i - 4.5 << " " << j + 5.5 << " " << k + 5.5 << std::endl;
          outfile << i + 5.5 << " " << j + 5.5 << " " << k + 5.5 << std::endl;
          outfile << i + 5.5 << " " << j - 4.5 << " " << k + 5.5 << std::endl;
        }
      }
    }
  }

  // Escreve as faces
  int vertexIndex = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          int v0 = vertexIndex++;
          int v1 = vertexIndex++;
          int v2 = vertexIndex++;
          int v3 = vertexIndex++;
          int v4 = vertexIndex++;
          int v5 = vertexIndex++;
          int v6 = vertexIndex++;
          int v7 = vertexIndex++;

          // Face frontal
          outfile << "4 " << v0 << " " << v1 << " " << v2 << " " << v3
                  << std::endl;
          // Face traseira
          outfile << "4 " << v4 << " " << v7 << " " << v6 << " " << v5
                  << std::endl;
          // Face esquerda
          outfile << "4 " << v0 << " " << v3 << " " << v7 << " " << v4
                  << std::endl;
          // Face direita
          outfile << "4 " << v1 << " " << v5 << " " << v6 << " " << v2
                  << std::endl;
          // Face superior
          outfile << "4 " << v0 << " " << v4 << " " << v5 << " " << v1
                  << std::endl;
          // Face inferior
          outfile << "4 " << v2 << " " << v6 << " " << v7 << " " << v3
                  << std::endl;
        }
      }
    }
  }

  // Fecha o arquivo
  outfile.close();

  std::cout << "Arquivo " << filename << " criado com sucesso." << std::endl;
}

// Implementação do método putBox
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int x = x0; x <= x1; x++) {
    for (int y = y0; y <= y1; y++) {
      for (int z = z0; z <= z1; z++) {
        putVoxel(x, y, z);
      }
    }
  }
}
// // Implementação do método cutBox
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}
// Implementação do método putSphere
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int x = xcenter - radius; x <= xcenter + radius; x++) {
    for (int y = ycenter - radius; y <= ycenter + radius; y++) {
      for (int z = zcenter - radius; z <= zcenter + radius; z++) {
        if ((pow(x - xcenter, 2) + pow(y - ycenter, 2) + pow(z - zcenter, 2)) <= pow(radius, 2)) {
          putVoxel(x, y, z);
        }
      }
    }
  }
}
// Implementação do método cutSphere
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = xcenter - radius; i <= xcenter + radius; i++) {
        for (int j = ycenter - radius; j <= ycenter + radius; j++) {
            for (int k = zcenter - radius; k <= zcenter + radius; k++) {
                if ((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) <= pow(radius, 2)) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}
// Implementação do método putEllipsoid
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
  for (int x = xcenter - rx; x <= xcenter + rx; x++) {
    for (int y = ycenter - ry; y <= ycenter + ry; y++) {
      for (int z = zcenter - rz; z <= zcenter + rz; z++) {
        if ((pow(x - xcenter, 2) / pow(rx, 2) + pow(y - ycenter, 2) / pow(ry, 2) + pow(z - zcenter, 2) / pow(rz, 2)) <= 1) {
          putVoxel(x, y, z);
        }
      }
    }
  }
}
// Implementação do método cutEllipsoid
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = xcenter - rx; i <= xcenter + rx; i++) {
        for (int j = ycenter - ry; j <= ycenter + ry; j++) {
            for (int k = zcenter - rz; k <= zcenter + rz; k++) {
                if ((pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2)) <= 1) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

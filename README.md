# NR no ns-3 - primeiros passos e hands-ons de análise de desempenho 

# Bolsistas de IC 2022
- Bolsista 01: RICARDO QUEIROZ DE FARIAS HENRIQUE SILVA
- Bolsista 02: DARIO GUILHERME DE MACEDO
- Bolsista 03: TBD
- Bolsista 04: TBD
- Aluno de Mestrado: LUCAS ISMAEL CAMPOS MEDEIROS
- Orientador: Vicente Angelo de Sousa Junior
- Co-orientadores: Daniel Rodrigues de Luna e Tarciana Cabral de Brito Guerra 
- Companheiros de grupo: , Ravan Novaes de Oliveira e Sildolfo Francisco Gomes Neto 

### Metas 2022.1
- Preparação de ambiente de prototipagem - Ricardo e Dario (**Hands-on 00**)
- Preparação de hands-on do artigo SBRT sobre beamforming (comparação path loss, shadowing e fading) - Lucas
- Preparação de hands-ons do artigo SBRT sobre cobertura indoor - Ricardo e Dario

## Fase 00: Preparação do ambiente de prática e desenvolvimento

### [Criação de máquina virtual Ubuntu Virtual box (UBUNTU 20.04)](https://github.com/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)  - [Link alternativo via nbviewer](http://nbviewer.jupyter.org/github/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)
**Objetivos:**
- Instalar Virtual Box no Windows
- Baixar e criar máquina virtual Ubuntu 20.04 no Windows

### Preparação do ambiente de trabalho [Github - o básico sobre repositórios](https://github.com/vicentesousa/2021_IC_Training/blob/main/fase_00/HD_01/f00_hd01.ipynb)
**Objetivos**
- Cadastramento no GitHub
- Criar repositorios no GitHub
- Submeter arquivos para repositórios do GitHub
- Editar o README.md

### Preparação do ambiente de trabalho - [Básico do Jupyter Notebook](https://github.com/vicentesousa/2021_IC_Training/blob/main/fase_00/HD_02/f00_hd02.ipynb)
**Objetivos**
- Instalar pacotes de suporte ao Jupyter Notebook (Anaconda, nbconvert, pandoc, extensions)
- Baixar, abrir, editar e criar Notebooks que executem blocos de código de Python (Python 3)
- Fazer um primeiro uso da linguagem Python 3 dentro dos Notebooks

### 5G-LENA
Começar com o conteúdo de [Pedir acesso ao 5G-LENA](https://5g-lena.cttc.es/download/)

Baixar e instala o [o ns-3-dev](https://gitlab.com/nsnam/ns-3-dev) e [5G-LENA](https://gitlab.com/cttc-lena/nr) 

**Objetivos**
- Instalar o ns-3 + 5G-LENA e dependências;

### Preparação do ambiente de trabalho - [Instalando o ns-3 e integrando com o VSCode](https://github.com/vicentesousa/2021_IC_Training/blob/main/fase_00/HD_03/f00_hd03.ipynb)
Começar com o conteúdo de [VISUAL STUDIO - AMBIENTES EM PYTHON](https://github.com/vicentesousa/DCO2004_2022/blob/main/notebooks/h01_utilizando_VisualStudio.ipynb)
Colocar o conteúdo de [Hands-on 0: VS Code e ns-3](https://github.com/vicentesousa/IC_LTE_ns3/blob/main/fase_01/HD_00/f01_hd00.ipynb)
**Objetivos**
- Instalar o ns3 e dependências (se já tiver feito, pular para o próximo objetivo);
- Instalar e configurar o VS Code;
- Integrar o ns3 com o VS Code.

## Fase 01: Treinamento do 5G-LENA 

### [Hands-on 01](https://github.com/vicentesousa/NR_IC_Training/blob/main/fase_01/HD_01/f01_hd01.ipynb)  - [Link alternativo via nbviewer](https://nbviewer.org/github/vicentesousa/NR_IC_Training/blob/main/fase_01/HD_01/f01_hd01.ipynb)
**Objetivos:**
- Entender e detalhar o exemplo **cttc-3gpp-channel-simple-ran.cc**;
- Testar os diversos parâmetros e verificar comportamentos;
- Prazo recomendado: 3 dias;
- Dário: Prazo: TBD . Feito: ;
- Ricardo: Prazo: TBD . Feito: .

### [Hands-on 02](https://github.com/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)  - [Link alternativo via nbviewer](http://nbviewer.jupyter.org/github/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)
**Objetivos:**
- Entender e detalhar o exemplo **cttc-nr-demo.cc**;
- Verificar as diferenças desse exemplo com o do hands-on 1. Apontar as principais diferenças no que se refere ao posicionamento e configuração do nrhelper
- Prazo recomendado: 3 dias;
- Dário: Prazo: TBD . Feito: ;
- Ricardo: Prazo: TBD . Feito: .


### [Hands-on 03](https://github.com/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)  - [Link alternativo via nbviewer](http://nbviewer.jupyter.org/github/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)
**Objetivos:**
- Entender e detalhar os exemplos **rem-beam-example.cc** e **rem-example.cc**;
- Gerar o REM com os valores padrões para os dois exemplos. Em seguida, gerar os dois tipos de REMs DL para: aumento no número de elementos de antenas, aumento no número de gNBs e tipos de antena diferentes. Por fim, entender e verificar comportamentos;
- Prazo recomendado: 3 dias;
- Dário: Prazo: TBD . Feito: ;
- Ricardo: Prazo: TBD . Feito: .

### [Hands-on 04](https://github.com/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)  - [Link alternativo via nbviewer](http://nbviewer.jupyter.org/github/vicentesousa/DCO2010_2022/blob/main/notebooks/H00_VM_VBox.ipynb)
**Objetivos:**
- Criar um REM com o cenário da Tarciana.
- Fazer um studo do posicionamento das gNBs: estudo de cobertura (indoor e outdoor) e em FR1 e FR2;
- Prazo recomendado: 7 dias;
- Dário: Prazo: TBD . Feito: ;
- Ricardo: Prazo: TBD . Feito: .

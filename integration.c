#include <stdlib.h>
#include <math.h>
#include <stdio.h>

  struct param{
    double k,m,x0,v0,Tmax,passi[4],vnLF;
  }par; // I declare a struct that will be filled from file with the FillParam function.

  struct param FillParam(struct param);
  void Euler(struct param);
  void EulerCromer(struct param);
  void MidPoint(struct param);
  void LeapFrog(struct param);
  void Verlet(struct param);
  void PlotAuto();

  int main(int argc, char *argv[]){
    int algo=argc>1 ? atoi(argv[1]):-1;// I'm saying that if the number of arguments passed to the command line is greater than 1, argv [1] is valid, otherwise argv [1] = - 1.
    struct param tmp;


    if(algo==1){ // based on the argument which step I run different algorithms.
        fprintf(stderr,"You are using Euler");
        tmp=FillParam(par);
        Euler(tmp);
      }else if(algo==2){
        fprintf(stderr,"You are using Euler Cromer");
        tmp=FillParam(par);
        EulerCromer(tmp);
      }else if(algo==3){
        fprintf(stderr,"You are using Mid Point");
        tmp=FillParam(par);
        MidPoint(tmp);
      }else if(algo==4){
        fprintf(stderr,"You are using Leap Frog");
        tmp=FillParam(par);
        LeapFrog(tmp);
      }else if(algo==5){
        tmp=FillParam(par);
        Verlet(tmp);
      }else if(algo==6){
        fprintf(stderr,"You are using all algorithms at the same time");
        tmp=FillParam(par);
        Euler(tmp);
        EulerCromer(tmp);
        MidPoint(tmp);
        LeapFrog(tmp);
        Verlet(tmp);
        PlotAuto();
      }else{  //if I don't pass arguments or pass too many argv [1] = - 1 so the code prints an error explaining how to pass the arguments.
        fprintf(stderr,"Enter 1 to run Euler, 2 to run Euler-Cromer, 3 to run Mid Point, 4 to run Leap Frog, 5 to run Verlet, and 6 to run all integration algorithms at the same time.\n");
      }
    }
//I read the function that fill parameter of struct.
  struct param FillParam(struct param pp){

    FILE *fp,*fd;
      fp=fopen("param.dat","r");
      fd=fopen("passi.dat","r");
        if(fp==NULL || fd==NULL){
          perror("Error opening the file"); //check for errors in opening the file
          exit(1);
        }
        fscanf(fp,"%lf",&pp.k); //you can find this parameter on file "param.dat" in the same order that the scanfs are written.
        fscanf(fp,"%lf",&pp.m);
        fscanf(fp,"%lf",&pp.x0);
        fscanf(fp,"%lf",&pp.v0);
        fscanf(fp,"%lf",&pp.Tmax); // I filled the struct with the parameters from the "param.dat" file.

        fprintf(stderr,"\nThe integration steps used within this program will be:\n");
        for(int i=0;i<=3;i++){
          fscanf(fd,"%lf",&pp.passi[i]);
          fprintf(stderr,"%lf\t",pp.passi[i]); // define the integration steps using an array defined in the struct and fill it from the "steps.dat" file.
        }
        fclose(fp);
        fclose(fd);
        fprintf(stderr,"\nThe parameters used within this program will be:\nk=%lg\nm=%lg\nx0=%lg\nv0=%lg\nTmax=%lg\nAnd will be used for all the previously mentioned integration steps.\n",pp.k,pp.m,pp.x0,pp.v0,pp.Tmax);
        return pp;
      }

//I write the function to implement Euler.

  void Euler(struct param par){
    double x,v,x1,v1;
    FILE *fd,*fp;
    v1=par.v0;
    x1=par.x0;

    fd=fopen("Eulero.dat","w");
    fp=fopen("E.dat","w");
    for(int l=0;l<4;l++){
      double  N=par.Tmax/par.passi[l];
      par.x0=x1;
      par.v0=v1;
        fprintf(fd,"#1:dt\t2:x\t3:v\t4:E\t5:dE\t6:ER\t\t per dt%d=%lf\n",l+1,par.passi[l]);

        for(int j=0;j<=(int)N;j++){

          x=par.x0+par.v0*par.passi[l];
          v=par.v0-((par.k*par.x0*par.passi[l])/par.m);
          double Energia=((par.m*v*v)/2)+((par.k*x*x)/2);
          double deltaEnergia=Energia-(((par.m*par.v0*par.v0)/2)+((par.k*par.x0*par.x0)/2));
          double EnergiaRelativa=deltaEnergia/Energia;
          par.x0=x;
          par.v0=v;

          fprintf(fd, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j*par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa); // print the results of the numerical integration on file.

          if(j==(int)N){
            fprintf(fp, "%lg\t%lf\t%lf\t%lf\t%lf\t%lf\n\n",par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa); // print the last lines of the integration, for each integration step, on a different file. This will help me to analyze the behavior of the various algorithms as the integration step changes.
          }
        }
        fprintf(fd, "\n\n"); // I need to use index on gnuplot.
      }
      fclose(fd);
      fclose(fp);
    }
// from now on the reasoning will be the same for all integration algorithms.
// I write the function to implement Euler Cromer.
  void EulerCromer(struct param par){
    double x,v,x1,v1;
    FILE *fd,*fp;
    v1=par.v0;
    x1=par.x0;
    fd=fopen("EuleroCromer.dat","w");
    fp=fopen("EC.dat","w");

    for(int l=0;l<4;l++){
      double  N=par.Tmax/par.passi[l];
      par.x0=x1;
      par.v0=v1;

        fprintf(fd,"#1:dt\t2:x\t3:v\t4:E\t5:dE\t6:ER\t\t per dt%d=%lf\n",l+1,par.passi[l]);

        for(int j=0;j<=(int)N;j++){
          v=par.v0-((par.k*par.x0*par.passi[l])/par.m);
          x=par.x0+v*par.passi[l];

          double Energia=((par.m*v*v)/2)+((par.k*x*x)/2);
          double deltaEnergia=Energia-(((par.m*par.v0*par.v0)/2)+((par.k*par.x0*par.x0)/2));
          double EnergiaRelativa=deltaEnergia/Energia;

          par.v0=v;
          par.x0=x;

          fprintf(fd, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j*par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa);
          if(j==(int)N){
            fprintf(fp, "%lg\t%lf\t%lf\t%lf\t%lf\t%lf\n\n",par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa);
          }
        }
        fprintf(fd, "\n\n");
      }
      fclose(fd);
      fclose(fp);
    }

// I write the function to implement the Mid Point algorithm.
    void MidPoint(struct param par){
      double x,v,x1,v1;
      FILE *fd,*fp;
      v1=par.v0;
      x1=par.x0;
      fd=fopen("PuntoCentrale.dat","w");
      fp=fopen("PC.dat","w");

      for(int l=0;l<4;l++){
        double  N=par.Tmax/par.passi[l];
        par.x0=x1;
        par.v0=v1;

        fprintf(fd,"#1:dt\t2:x\t3:v\t4:E\t5:dE\t6:ER\t\t per dt%d=%lf\n",l+1,par.passi[l]);

        for(int j=0;j<=(int)N;j++){

          v=par.v0-((par.k*par.x0*par.passi[l])/par.m);
          x=par.x0+0.5*(v+par.v0)*par.passi[l];

          double Energia=((par.m*v*v)/2)+((par.k*x*x)/2);
          double deltaEnergia=Energia-(((par.m*par.v0*par.v0)/2)+((par.k*par.x0*par.x0)/2));
          double EnergiaRelativa=deltaEnergia/Energia;

          par.v0=v;
          par.x0=x;

          fprintf(fd, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j*par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa);
          if(j==(int)N){
            fprintf(fp, "%lg\t%lf\t%lf\t%lf\t%lf\t%lf\n\n",par.passi[l],x,v,Energia,deltaEnergia,EnergiaRelativa);
          }
        }
        fprintf(fd,"\n\n");
      }
      fclose(fd);
      fclose(fp);
    }
// I write the function to implement Leap-Frog.
    void LeapFrog(struct param par){
      double v,x1,v1;
      FILE *fd,*fp;
      v1=par.v0;
      x1=par.x0;
      fd=fopen("LeapFrog.dat","w");
      fp=fopen("LF.dat","w");

      for(int l=0;l<4;l++){
        double  N=par.Tmax/par.passi[l];
        par.x0=x1;
        par.v0=v1;
        par.vnLF=(par.v0-(par.k/par.m)*par.passi[l]/2.);
        fprintf(fd,"#1:dt\t2:x\t3:v\t4:E\t5:dE\t6:ER\t\t per dt%d=%lf\n",l+1,par.passi[l]);

        for(int j=0;j<=(int)N+0.5;j++){
          par.x0=par.x0+par.vnLF*par.passi[l];
          par.vnLF=par.vnLF-((par.k*par.x0*par.passi[l])/par.m);

          v = par.vnLF - ((par.k*par.x0*par.passi[l])/par.m);

          double Energia=((par.m*v*v)/2)+((par.k*par.x0*par.x0)/2);
          double deltaEnergia=Energia-(((par.m*v1*v1)/2)+((par.k*x1*x1)/2));
          double EnergiaRelativa=deltaEnergia/Energia;

          fprintf(fd, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j*par.passi[l],par.x0,v,Energia,deltaEnergia,EnergiaRelativa);
          if(j==(int)N){
            fprintf(fp, "%lg\t%lf\t%lf\t%lf\t%lf\t%lf\n\n",par.passi[l],par.x0,v,Energia,deltaEnergia,EnergiaRelativa);
          }
        }
        fprintf(fd,"\n\n");
      }
      fclose(fd);
      fclose(fp);
    }
// I write the function to implement self-contained Verlet.
    void Verlet(struct param par) {
      double x,x1,v1;
      FILE *fd,*fp;
      v1=par.v0;
      x1=par.x0;
      fd=fopen("Verlet.dat","w");
      fp=fopen("V.dat","w");

      for(int l=0;l<4;l++){
        double  N=par.Tmax/par.passi[l];
        par.x0=x1;
        par.v0=v1;

        fprintf(fd,"#1:dt\t2:x\t3:v\t4:E\t5:dE\t6:ER\t\t per dt%d=%lf\n",l+1,par.passi[l]);

        for(int j=0;j<=(int)N;j++){
          x=par.x0;
          par.x0=par.x0+par.v0*par.passi[l]-0.5*((par.k*par.x0*par.passi[l]*par.passi[l])/par.m);
          par.v0=par.v0-0.5*(par.k*par.x0/par.m+par.k*x/par.m)*par.passi[l];

          double Energia=((par.m*par.v0*par.v0)/2)+((par.k*par.x0*x)/2);
          double deltaEnergia=Energia-(((par.m*par.v0*par.v0)/2)+((par.k*par.x0*par.x0)/2));
          double EnergiaRelativa=deltaEnergia/Energia;

          fprintf(fd, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j*par.passi[l],par.x0,par.v0,Energia,deltaEnergia,EnergiaRelativa);
          if(j==(int)N){
            fprintf(fp, "%lg\t%lf\t%lf\t%lf\t%lf\t%lf\n\n",par.passi[l],par.x0,par.v0,Energia,deltaEnergia,EnergiaRelativa);
          }
        }
        fprintf(fd,"\n\n");
      }
      fclose(fd);
      fclose(fp);
  }
// This function automatically plots a graph of the relative energy as a function of the integration step by comparing it for each algorithm used. If you don't have gnuplot and you don't have a file that has gnuplot code implemented don't use this function.
  void PlotAuto(){

    FILE *gp;
    gp=popen("gnuplot","w");

      fprintf(gp,"load 'Fit.gnu'\n");
      fprintf(gp,"save 'IntegrationError.plt'")

    pclose(gp);
  }

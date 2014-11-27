//tun with root -l plotter_smearing.C

plotter_smearing(){
  ifstream infile; 
  //infile.open("tmp/Smearing.txt");
  infile.open("tmp/Smearing_afterFullProcedure.txt");

  TH1F* gauss=new TH1F("gauss","gauss",100,-3,3);

  double g=0;

  if (infile.is_open())
    {
    cout<<"File aperto"<<endl;
      while ( infile.good() )
	{
	  infile>>g;
	  gauss->Fill(g);
	}
      infile.close();
    }



   gauss->Draw();
   infile.close();

}


/* If you want to write:
  ofstream outfile;
  outfile.open("tmp/Smearing.txt",ios::trunc);
  outfile <<event.smearings_ele1[i] <<endl;
  outfile.close();
*/

#ifndef WIELD_IO_READERMACROS_H
#define WIELD_IO_READERMACROS_H

#define WIELD_IO_READ_CRYSTAL(NUM)					\
  Wield::Series::CosSeries *crystal##NUM##temp;				\
  if (reader.Find("C_"#NUM,Reader::DEPRICATED))				\
    {									\
      crystal##NUM##temp =						\
	new Wield::Series::CosSeries(reader.Read<string>("C_"#NUM));	\
    }									\
  else									\
    {									\
      crystal##NUM##temp =						\
      new Wield::Series::CosSeries(reader, "Crystal"#NUM);		\
    }									\
  Wield::Series::CosSeries crystal##NUM(crystal##NUM##temp);		\
  delete crystal##NUM##temp;						

#define WIELD_IO_READ_CRYSTAL_ORIENTATION(STRUCTNAME,NUM)		\
  Matrix3d omega##NUM;							\
  if (reader.Find(STRUCTNAME,"X"#NUM) &&				\
      reader.Find(STRUCTNAME,"Y"#NUM))					\
    {									\
      omega##NUM =							\
	createMatrixFromXY						\
	(reader.Read<Eigen::Vector3d>(STRUCTNAME,"X"#NUM),		\
	 reader.Read<Eigen::Vector3d>(STRUCTNAME,"Y"#NUM));		\
    }									\
  else if (reader.Find(STRUCTNAME,"Y"#NUM) &&				\
	   reader.Find(STRUCTNAME,"Z"#NUM))				\
    {									\
      omega##NUM =							\
	createMatrixFromYZ						\
	(reader.Read<Eigen::Vector3d>(STRUCTNAME,"Y"#NUM),		\
	 reader.Read<Eigen::Vector3d>(STRUCTNAME,"Z"#NUM));		\
    }									\
  else if (reader.Find(STRUCTNAME,"Z"#NUM) &&				\
	   reader.Find(STRUCTNAME,"X"#NUM))				\
    {									\
      omega##NUM =							\
	createMatrixFromZX						\
	(reader.Read<Eigen::Vector3d>(STRUCTNAME,"Z"#NUM),		\
	 reader.Read<Eigen::Vector3d>(STRUCTNAME,"X"#NUM));		\
    }									\
  else WIELD_EXCEPTION_NEW("Missing two vectors to specify omega"#NUM); 

#define WIELD_IO_READ_PARAMETERS(STRUCTNAME)				\
  double a,b,stdDev;							\
  if (reader.Find(STRUCTNAME,"f_constants",Reader::DEPRICATED))		\
    {									\
      string f_constants =						\
	reader.Read<string>(STRUCTNAME,"f_constants");			\
      Reader::Reader constantsReader(f_constants, "$", "#", "...");	\
      if (reader.Find(STRUCTNAME,"A"))					\
	a = reader.Read<double>(STRUCTNAME,"A");			\
      else								\
	a = constantsReader.Read<double>("A");				\
      if (reader.Find(STRUCTNAME,"B"))					\
	b = reader.Read<double>(STRUCTNAME,"B");			\
      else								\
	b = constantsReader.Read<double>("B");				\
      if (reader.Find(STRUCTNAME,"StdDev"))				\
	stdDev = reader.Read<double>(STRUCTNAME,"StdDev");		\
      else								\
	stdDev = constantsReader.Read<double>("StdDev");		\
    }									\
  else									\
    {									\
      a = reader.Read<double>(STRUCTNAME,"A");				\
      b = reader.Read<double>(STRUCTNAME,"B");				\
      stdDev = reader.Read<double>(STRUCTNAME,"StdDev");		\
    }



#endif

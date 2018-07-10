#include "fvCFD.H"

int main(int argc, char *argv[])
{
	// Read
	Foam::argList args(argc,argv);
	if(not args.checkRootCase()) Foam::FatalError.exit();

	Foam::Time runTime(Foam::Time::controlDictName, args);
	instantList timeDirs = timeSelector::select0(runTime, args);

	forAll(timeDirs, timeI){
		runTime.setTime(timeDirs[timeI], timeI);
		Foam::fvMesh mesh
		(
			Foam::IOobject
			(
				Foam::fvMesh::defaultRegion,
				runTime.timeName(),
				runTime,
				Foam::IOobject::MUST_READ
			)
		);

		volScalarField volume
		(
			Foam::IOobject
			(
				"volume",
				runTime.timeName(),
				mesh,
				Foam::IOobject::NO_READ,
				Foam::IOobject::AUTO_WRITE
			),
			mesh,
			dimensionedScalar("volume", dimVolume, 0.0)
		);

		forAll(mesh.cells(), cid){
			volume[cid] = mesh.V()[cid];
		}

		volume.write();
	}


	return 0;
}

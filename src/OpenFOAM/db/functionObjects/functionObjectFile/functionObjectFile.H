/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::functionObjectFile

Description
    Base class for output file data handling

See Also
    Foam::functionObject
    Foam::OutputFilterFunctionObject

SourceFiles
    functionObjectFile.C

\*---------------------------------------------------------------------------*/

#ifndef functionObjectFile_H
#define functionObjectFile_H

#include "objectRegistry.H"
#include "OFstream.H"
#include "PtrList.H"
#include "HashSet.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                     Class functionObjectFile Declaration
\*---------------------------------------------------------------------------*/

class functionObjectFile
{
private:

    // Private data

        //- Reference to the database
        const objectRegistry& obr_;

        //- Prefix
        const word prefix_;

        //- File names
        wordHashSet names_;

        //- File pointer
        PtrList<OFstream> filePtrs_;


protected:

    // Protected Member Functions

        //- Return the base directory for output
        virtual fileName baseFileDir() const;

        //- Return the base directory for the current time value
        virtual fileName baseTimeDir() const;

        //- Create the output file
        virtual void createFiles();

        //- File header information
        virtual void writeFileHeader(const label i = 0);

        //- Write function
        virtual void write();

        //- Reset the list of names from a wordList
        virtual void resetNames(const wordList& names);

        //- Reset the list of names to a single name entry
        virtual void resetName(const word& name);

        //- Disallow default bitwise copy construct
        functionObjectFile(const functionObjectFile&);

        //- Disallow default bitwise assignment
        void operator=(const functionObjectFile&);


public:

    //- Folder prefix
    static const word outputPrefix;

    // Constructors

        //- Construct null
        functionObjectFile(const objectRegistry& obr, const word& prefix);

        //- Construct from components
        functionObjectFile
        (
            const objectRegistry& obr,
            const word& prefix,
            const word& name
        );

        //- Construct from components
        functionObjectFile
        (
            const objectRegistry& obr,
            const word& prefix,
            const wordList& names
        );


    //- Destructor
    virtual ~functionObjectFile();


    // Member Functions

        //- Return const access to the names
        const wordHashSet& names() const;

        //- Return access to the file (if only 1)
        OFstream& file();

        //- Return access to the files
        PtrList<OFstream>& files();

        //- Return file 'i'
        OFstream& file(const label i);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// NOTE - This code incomplete and requires underlined portions
// to be replaced with code to read values from your file format.

#include <avtIntervalTree.h>

// STMD version of GetAuxiliaryData.
void *
avtXXXXFileFormat::GetAuxiliaryData(const char *var,
    int domain, const char *type, void *,
    DestructorFunction &df)
{
    void *retval = 0;

    if(strcmp(type, AUXILIARY_DATA_DATA_EXTENTS) == 0)
    {
        // Read the number of domains for the mesh.
        int ndoms = READ NUMBER OF DOMAINS FROM FILE;

        // Read the min/max values for each domain of the
        // "var" variable. This information should be in
        // a single file and should be available without
        // having to read the real data.
        double *minvals = new double[ndoms];
        double *maxvals = new double[ndoms];
        READ ndoms DOUBLE VALUES INTO minvals ARRAY.
        READ ndoms DOUBLE VALUES INTO maxvals ARRAY.

        // Create an interval tree
        avtIntervalTree *itree = new avtIntervalTree(ndoms, 1);
        for(int dom = 0; dom < ndoms; ++dom)
        {
            double range[2];
            range[0] = minvals[dom];
            range[1] = maxvals[dom];
            itree->AddElement(dom, range);
        }
        itree->Calculate(true);

        // Delete temporary arrays.
        delete [] minvals;
        delete [] maxvals;

        // Set return values
        retval = (void *)itree;
        df = avtIntervalTree::Destruct;
    }

    return retval;
}

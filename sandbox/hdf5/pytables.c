/* pytables.c
 *  
 *  TODO - license information (BSD) and authors
 *
 */

#include "pytables.h"



/* Function: find_attr
 *
 * Purpose: operator function used by find_attribute
 */
static herr_t find_attr(hid_t loc_id, const char *name, void *op_data)
{
    /* Define a default zero value for return. This will cause the
     * iterator to continue if the palette attribute is not found yet.
     */
    int ret = 0;

    char *attr_name = (char *)op_data;

    /* Shut the compiler up */
    loc_id = loc_id;

    /* Define a positive value for return value if the attribute was
     * found. This will cause the iterator to immediately return that
     * positive value, indicating short-circuit success
     */
    if(strcmp(name, attr_name) == 0)
        ret = 1;

    return ret;
}


/* Function: find_attribute
 *
 * Purpose: Inquires if an attribute named attr_name exists attached
 *          to the object loc_id.
 *
 * Comments:
 *  The function uses H5Aiterate with the operator function find_attr
 *
 * Return:
 *  Success: The return value of the first operator that
 *              returns non-zero, or zero if all members were
 *              processed with no operator returning non-zero.
 *
 *  Failure: Negative if something goes wrong within the
 *              library, or the negative value returned by one
 *              of the operators.
 */
herr_t find_attribute(hid_t loc_id, const char *attr_name)
{
    unsigned int attr_num;
    herr_t ret;

    attr_num = 0;
    ret = H5Aiterate(loc_id, &attr_num, find_attr, (void *)attr_name);

    return ret;
}


/* Function: set_attribute_string
 *
 * Purpose: Creates and writes a string attribute named attr_name
 *          and attaches it to the object specified by obj_id
 *
 * Return: Success: 0, Failure: -1
 *
 * Comments: If the attribute already exists, it is overwritten.
 */
herr_t set_attribute_string(hid_t obj_id,
                            const char *attr_name,
                            const char *attr_data)
{
    hid_t   attr_type;
    hid_t   attr_size;
    hid_t   attr_space_id;
    hid_t   attr_id;
    int     has_attr;
    herr_t  status;

    /* Create the attribute */
    attr_type = H5Tcopy(H5T_C_S1);
    if(attr_type < 0) goto out;

    attr_size = strlen(attr_data) + 1;   /* extra null term */

    status = H5Tset_size(attr_type, (size_t)attr_size);
    if(status < 0) goto out;

    status = H5Tset_strpad(attr_type, H5T_STR_NULLTERM);
    if(status < 0) goto out;

    attr_space_id = H5Screate(H5S_SCALAR);
    if(status < 0) goto out;

    /* Verify if the attribute already exists */
    has_attr = find_attribute(obj_id, attr_name);

    /* The attribute already exists, delete it */
    if(has_attr == 1)
    {
        status = H5Adelete(obj_id, attr_name);
        if(status < 0) goto out;
    }

    /* Create and write the attribute */

    attr_id = H5Acreate(obj_id, attr_name, attr_type, attr_space_id, 
                        H5P_DEFAULT);
    if(attr_id < 0) goto out;

    status = H5Awrite(attr_id, attr_type, attr_data);
    if(status < 0) goto out;

    status = H5Aclose(attr_id);
    if(status < 0) goto out;

    status = H5Sclose(attr_space_id);
    if(status < 0) goto out;

    status = H5Tclose(attr_type);
    if(status < 0) goto out;


    return 0;

out:
    return -1;
}


herr_t make_array(hid_t loc_id,
                  const char *dset_name,
                  const int rank,
                  const hsize_t *dims,
                  hid_t type_id,
                  const void *data)
{
    hid_t   dataset_id, space_id;
    hsize_t *maxdims = NULL;
    hid_t   plist_id = 0;
    herr_t  status;
    
    /* Create the data space for the dataset */
    space_id = H5Screate_simple(rank, dims, maxdims);
    if(space_id < 0) return -1;

    /* Create the dataset */
    dataset_id = H5Dcreate(loc_id, dset_name, type_id, space_id, plist_id);
    if(dataset_id < 0) goto out;

    /* Write the dataset only if there is data to write */
    if(data)
    {
        status = H5Dwrite(dataset_id, type_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          data);
        if(status < 0) goto out;
    }

    /* Terminate access to the data space. */
    status = H5Sclose(space_id);
    if(status < 0) return -1;

    /* End access to the property list */
    if(plist_id)
    {
        status = H5Pclose(plist_id);
        if(status < 0) goto out;
    }

    /*
     * Set the conforming array attributes
     */

    /* Attach the CLASS attribute */
    status = set_attribute_string(dataset_id, "CLASS", "ARRAY");
    if(status < 0) goto out;

    /* Attach the FLAVOR attribute */
    status = set_attribute_string(dataset_id, "FLAVOR", "Numeric");
    if(status < 0) goto out;

    /* Attach the VERSION attribute */
    status = set_attribute_string(dataset_id, "VERSION", "2.3");
    if(status < 0) goto out;

    /* Attach the TITLE attribute */
    status = set_attribute_string(dataset_id, "TITLE", "Box array!");
    if(status < 0) goto out;

    /* Release resources */
    /* if(maxdims) free(maxdims); */
    return dataset_id;

out:
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    /* if(maxdims) free(maxdims); */
    /* if(dims_chunk) free(dims_chunk); */
    return -1;
}

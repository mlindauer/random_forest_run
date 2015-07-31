#ifndef RFR_SPLIT_BASE_HPP
#define RFR_SPLIT_BASE_HPP

#include <vector>
#include <array>
#include "data_containers/data_container_base.hpp"



namespace rfr{

template <const int k, typename num_type = float, typename index_type = unsigned int>
class k_ary_split_base{
  public:
	/** \brief member function to find the optimal split for a subset of the data and features
	 *
	 * Defining the interface that every split has to implement. Unfortunately, virtual constructors are
	 * not allowed in C++, so this function is called instead. Code in the nodes and the tree will only use the 
	 * default constructor and the methods below for training and prediction.
	 * 
	 * \param data the container holding the training data
	 * \param features_to_try a vector with the indices of all the features that can be considered for this split
	 * \param indices a vector containing the subset of data point indices to be considered (output!)
	 * \param split_indices_it iterators into indices specifying where to split the data for the children. Number of iterators is k+1, for easier iteration
	 * 
	 * \return float the loss of the found split
	 */
	virtual num_type find_best_split(const rfr::data_container_base<num_type, index_type> &data,
									const std::vector<index_type> &features_to_try,
									std::vector<index_type> & indices,
									std::array<typename std::vector<index_type>::iterator, k+1> &split_indices_it) = 0;

	/** \brief operator telling into which child the given feature vector falls
	 * 
	 * \param feature_vector an array containing a valid (in terms of size and values!) feature vector
	 * 
	 * \return index_type index of the child into which this feature falls
	 */
	virtual index_type operator() (num_type *feature_vector) = 0;
	
	virtual void print_info() = 0;
};



}//namespace rfr
#endif

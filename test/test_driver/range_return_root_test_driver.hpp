//  Copyright Klaus Triendl 2020. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_TEST_TEST_DRIVER_RANGE_RETURN_BASE_TEST_DRIVER_HPP_INCLUDED
#define BOOST_RANGE_TEST_TEST_DRIVER_RANGE_RETURN_BASE_TEST_DRIVER_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

namespace boost
{
    namespace range_test
    {
        // check the results of an algorithm that returns
        // a range_return featuring root iterators.
        //
        // This version is the general version. It should never be called.
        // All calls should invoke specialized implementations.
        template< range_return_value return_type >
        struct check_results
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                RootIterator           test_it,
                RootIterator           reference_it
                )
            {
                BOOST_ASSERT( false );
            }
        };

        // check the results of an algorithm that returns
        // a 'found' root iterator
        template< >
        struct check_results<return_root_found>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                RootIterator           test_it,
                RootIterator           reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                    test.begin(), test.end() );

                BOOST_CHECK_EQUAL( std::distance(root_of(test.begin()), test_it),
                   std::distance(root_of(reference.begin()), reference_it) );
            }
        };

        // check the results of an algorithm that returns
        // a 'next(found)' root iterator
        template< >
        struct check_results<return_root_next>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                RootIterator           test_it,
                RootIterator           reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                    test.begin(), test.end() );

                if (reference_it == root_of(reference.end()))
                {
                    BOOST_CHECK( test_it == root_of(test.end()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL(
                        std::distance(root_of(test.begin()), test_it),
                        std::distance(root_of(reference.begin()), reference_it) + 1);
                }
            }
        };

        // check the results of an algorithm that returns
        // a 'prior(found)' root iterator
        template< >
        struct check_results<return_root_prior>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                    test.begin(), test.end() );

                if (reference_it == root_of(reference.begin()))
                {
                    BOOST_CHECK( test_it == root_of(test.begin()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL(
                        std::distance(root_of(test.begin()), test_it) + 1,
                        std::distance(root_of(reference.begin()), reference_it));
                }
            }
        };

        // check the results of an algorithm that returns
        // a '[begin, found)' root iterator range
        template< >
        struct check_results<return_root_begin_found>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS(
                    reference.begin(), reference.end(),
                    test.begin(), test.end()
                    );

                BOOST_CHECK( test_rng.begin() == root_of(test.begin()) );

                BOOST_CHECK_EQUAL_COLLECTIONS(
                    root_of(reference.begin()), reference_it,
                    boost::begin(test_rng), boost::end(test_rng)
                    );
            }
        };

        // check the results of an algorithm that returns
        // a '[begin, next(found))' root iterator range
        template< >
        struct check_results<return_root_begin_next>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS(
                    reference.begin(), reference.end(),
                    test.begin(), test.end()
                    );

                BOOST_CHECK( test_rng.begin() == root_of(test.begin()) );

                if (reference_it == root_of(reference.end()))
                {
                    BOOST_CHECK( test_rng.end() == root_of(test.end()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL_COLLECTIONS(
                        root_of(reference.begin()), boost::next(reference_it),
                        test_rng.begin(), test_rng.end());
                }
            }
        };

        // check the results of an algorithm that returns
        // a '[begin, prior(found))' root iterator range
        template< >
        struct check_results<return_root_begin_prior>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                    test.begin(), test.end() );

                BOOST_CHECK( test_rng.begin() == root_of(test.begin()) );

                if (reference_it == root_of(reference.begin()))
                {
                    BOOST_CHECK( boost::end(test_rng) == root_of(test.begin()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL( std::distance(boost::begin(test_rng), boost::end(test_rng)) + 1,
                                       std::distance(root_of(reference.begin()), reference_it) );
                }
            }
        };

        // check the results of an algorithm that returns
        // a '[found, end)' root iterator range
        template< >
        struct check_results<return_root_found_end>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                    test.begin(), test.end() );

                BOOST_CHECK_EQUAL(
                    std::distance(root_of(test.begin()), boost::begin(test_rng)),
                    std::distance(root_of(reference.begin()), reference_it));

                BOOST_CHECK( boost::end(test_rng) == root_of(test.end()) );
            }
        };

        // check the results of an algorithm that returns
        // a '[next(found), end)' root iterator range
        template< >
        struct check_results<return_root_next_end>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS(
                    reference.begin(), reference.end(),
                    test.begin(), test.end()
                    );

                BOOST_CHECK( test_rng.end() == root_of(test.end()) );

                if (reference_it == root_of(reference.end()))
                {
                    BOOST_CHECK( test_rng.begin() == root_of(test.end()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL_COLLECTIONS(
                        boost::next(reference_it), root_of(reference.end()),
                        test_rng.begin(), test_rng.end()
                        );
                }
            }
        };

        // check the results of an algorithm that returns
        // a 'prior(found), end)' root iterator range
        template< >
        struct check_results<return_root_prior_end>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS(
                    reference.begin(), reference.end(),
                    test.begin(), test.end()
                    );

                BOOST_CHECK( test_rng.end() == root_of(test.end()) );

                if (reference_it == root_of(reference.begin()))
                {
                    BOOST_CHECK( test_rng.begin() == root_of(test.begin()) );
                }
                else
                {
                    BOOST_CHECK_EQUAL_COLLECTIONS(
                        boost::prior(reference_it), root_of(reference.end()),
                        test_rng.begin(), test_rng.end()
                        );
                }
            }
        };

        // check the results of an algorithm that returns
        // a '[begin, end)' root iterator range
        template< >
        struct check_results<return_root_begin_end>
        {
            template< class View, class RootIterator >
            static void test(
                View&                  test,
                View&                  reference,
                iterator_range<RootIterator> test_rng,
                RootIterator                 reference_it
                )
            {
                BOOST_CHECK_EQUAL_COLLECTIONS(
                    reference.begin(), reference.end(),
                    test.begin(), test.end()
                    );

                BOOST_CHECK( test_rng.begin() == root_of(test.begin()) );
                BOOST_CHECK( test_rng.end() == root_of(test.end()) );
            }
        };

        // A test driver to exercise a test through all of the range_return
        // combinations featuring root iterators.
        //
        // The test driver also contains the code required to check the
        // return value correctness.
        //
        // The TestPolicy needs to implement two functions:
        //
        // - perform the boost range version of the algorithm that returns
        //   a range_return<View,return_type>::type
        // template<range_return_value return_type, class View>
        // BOOST_DEDUCED_TYPENAME range_return<View,return_type>::type
        // test(View& cont);
        //
        // - perform the reference std version of the algorithm that
        //   returns the standard iterator result
        // template<class View>
        // BOOST_DEDUCED_TYPENAME range_iterator<View>::type
        // reference(View& rng);
        class range_return_root_test_driver
        {
        public:
            template< class View,
                      class TestPolicy >
            void operator()(View& rng, TestPolicy policy)
            {
                test_range_iter               (rng, policy);
                test_range<return_root_found,View,TestPolicy>      ()(rng, policy);
                test_range<return_root_next,View,TestPolicy>       ()(rng, policy);
                test_range<return_root_prior,View,TestPolicy>      ()(rng, policy);
                test_range<return_root_begin_found,View,TestPolicy>()(rng, policy);
                test_range<return_root_begin_next,View,TestPolicy> ()(rng, policy);
                test_range<return_root_begin_prior,View,TestPolicy>()(rng, policy);
                test_range<return_root_found_end,View,TestPolicy>  ()(rng, policy);
                test_range<return_root_next_end,View,TestPolicy>   ()(rng, policy);
                test_range<return_root_prior_end,View,TestPolicy>  ()(rng, policy);
                test_range<return_root_begin_end,View,TestPolicy>  ()(rng, policy);
            }

        private:
            template< class View, class TestPolicy >
            void test_range_iter(
                View&          rng,
                TestPolicy     policy
                )
            {
                typedef BOOST_DEDUCED_TYPENAME range_iterator<View>::type iterator_t;
                typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator_t>::type root_iterator_t;

                View reference(rng);
                View test(rng);

                root_iterator_t test_it = policy.test_iter(test);
                root_iterator_t reference_it = policy.reference(reference);

                check_results<return_root_found>::test(test, reference,
                                                       test_it, reference_it);
            }

            template< range_return_value result_type, class View, class TestPolicy >
            struct test_range
            {
                void operator()(View& rng, TestPolicy policy)
                {
                    typedef BOOST_DEDUCED_TYPENAME range_iterator<View>::type iterator_t;
                    typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator_t>::type root_iterator_t;
                    typedef BOOST_DEDUCED_TYPENAME range_return<View, result_type>::type range_return_t;
                    typedef BOOST_DEDUCED_TYPENAME TestPolicy::template test_range<result_type> test_range_t;

                    View reference(rng);
                    View test(rng);

                    test_range_t test_range_fn;
                    range_return_t test_rng = test_range_fn(policy, test);
                    root_iterator_t reference_it = policy.reference(reference);

                    check_results<result_type>::test(test, reference,
                                                     test_rng, reference_it);
                }
            };
        };
    }
}

#endif // include guard

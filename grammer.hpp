#ifndef GRAMMER_H
#define GRAMMER_H

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include <vector>
#include "point.h"
#include "index.h"

BOOST_FUSION_ADAPT_STRUCT
(
    Point,
    (double, x)
    (double, y)
    (double, z)
    )

    BOOST_FUSION_ADAPT_STRUCT
    (
        Index,
        (int, a)
        (int, b)
        (int, c)
        )

namespace Grammer
{

    //grammer to parse Points (x,y,z) coordinates
    namespace qi = boost::spirit::qi;
    namespace repo = boost::spirit::repository;
    template <typename Iterator>

    struct PointParser : public qi::grammar<Iterator, std::vector<Point>(), qi::space_type>
    {

        PointParser() : PointParser::base_type(start, "PointGrammar")
        {

            singlePoint = qi::double_ >> qi::double_ >> qi::double_ >> *qi::lit(",");
            comment = qi::lit("#") >> *(qi::char_("a-zA-Z.") - qi::eol);
            prefix = repo::seek[qi::lexeme[qi::skip[qi::lit("point") >> qi::lit("[") >> *comment]]];
            start %= prefix >> qi::repeat[singlePoint];

        }

        qi::rule<Iterator, Point(), qi::space_type>              singlePoint;
        qi::rule<Iterator, qi::space_type>                       comment;
        qi::rule<Iterator, qi::space_type>                       prefix;
        qi::rule<Iterator, std::vector<Point>(), qi::space_type> start;

    };



    //grammer to parse CoordiIndex
    template <typename Iterator>

    struct IndexParser : public qi::grammar<Iterator, std::vector<Index>(), qi::space_type>
    {

        IndexParser() : IndexParser::base_type(start, "IndexGrammar")
        {

            singleIndex = qi::int_ >> qi::int_ >> qi::int_ >> *qi::lit("-1");
            comment = qi::lit("#") >> *(qi::char_("a-zA-Z.") - qi::eol);
            prefix = repo::seek[qi::lexeme[qi::skip[qi::lit("coordIndex") >> qi::lit("[") >> *comment]]];
            start %= prefix >> qi::repeat[singleIndex];

        }

        qi::rule<Iterator, Index(), qi::space_type>              singleIndex;
        qi::rule<Iterator, qi::space_type>                       comment;
        qi::rule<Iterator, qi::space_type>                       prefix;
        qi::rule<Iterator, std::vector<Index>(), qi::space_type> start;

    };
}

#endif

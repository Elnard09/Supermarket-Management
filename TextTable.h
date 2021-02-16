#pragma once
#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>

class TextTable {

	/*
	TextTable t( '-', '|', '+' );
		t.add( "Audit Trail Info" );
		t.endOfRow();
		cout << t
	*/

    public:
    enum Alignment { LEFT, RIGHT };
    typedef std::vector< std::string > Row;
    TextTable() :
        _horizontal( '-' ),
        _vertical( '|' ),
        _corner( '+' ),
		_has_ruler(true)
    {}

    TextTable( char horizontal, char vertical, char corner ) :
        _horizontal( horizontal ),
        _vertical( vertical ),
        _corner( corner ),
		_has_ruler(true)
    {}

    explicit TextTable( char vertical ) :
        _horizontal( '\0' ),
        _vertical( vertical ),
        _corner( '\0' ),
		_has_ruler( false )
    {}

    void setAlignment( unsigned i, Alignment alignment )
    {
        _alignment[ i ] = alignment;
    }

    Alignment alignment( unsigned i ) const
    { return _alignment[ i ]; }

    char vertical() const
    { return _vertical; }

    char horizontal() const
    { return _horizontal; }

    void add( std::string const & content )
    {
        _current.push_back( content );
    }

    void endOfRow()
    {
        _rows.push_back( _current );
        _current.assign( 0, "" );
    }

    /*template <typename Iterator>
    void addRow( Iterator begin, Iterator end )
    {
        for( auto int i = begin; i != end; ++i ) {
           add( * i );
        }
        endOfRow();
    }
    template <typename Container>
    void addRow( Container const & container )
    {
        addRow( container.begin(), container.end() );
    }*/

    std::vector< Row > const & rows() const
    {
        return _rows;
    }

    void setup() const
    {
        determineWidths();
        setupAlignment();
    }

    std::string ruler() const
    {
        std::string result;
        result += _corner;
        for( auto width = _width.begin(); width != _width.end(); ++ width ) {
            result += repeat( * width, _horizontal );
            result += _corner;
        }

        return result;
    }

    int width( unsigned i ) const
    { return _width[ i ]; }

	bool has_ruler() const { return _has_ruler;}

    private:
    const char _horizontal;
    const char _vertical;
    const char _corner;
    const bool _has_ruler;
    Row _current;
    std::vector< Row > _rows;
    std::vector< unsigned > mutable _width;
    std::map< unsigned, Alignment > mutable _alignment;

    static std::string repeat( unsigned times, char c )
    {
        std::string result;
        for( ; times > 0; -- times )
            result += c;

        return result;
    }

    unsigned columns() const
    {
        return _rows[ 0 ].size();
    }

    void determineWidths() const
    {
        _width.assign( columns(), 0 );
		auto rowIterator = _rows.begin();
        for (rowIterator; rowIterator != _rows.end(); ++ rowIterator ) {
            Row const & row = * rowIterator;
            for ( unsigned i = 0; i < row.size(); ++i ) {
                _width[ i ] = _width[ i ] > row[ i ].size() ? _width[ i ] : row[ i ].size();
            }
        }
    }

    void setupAlignment() const
    {
        for ( unsigned i = 0; i < columns(); ++i ) {
            if ( _alignment.find( i ) == _alignment.end() ) {
                _alignment[ i ] = Alignment::LEFT;
            }
        }
    }
};

inline std::ostream & operator<<( std::ostream & stream, TextTable const & table )
{
    table.setup();
	if (table.has_ruler()) {
	    stream << table.ruler() << "\n";
	}
	auto rowIterator = table.rows().begin();
    for (rowIterator; rowIterator != table.rows().end(); ++ rowIterator ) {
        TextTable::Row const & row = * rowIterator;
        stream << table.vertical();
        for ( unsigned i = 0; i < row.size(); ++i ) {
            auto alignment = table.alignment( i ) == TextTable::Alignment::LEFT ? std::left : std::right;
            stream << std::setw( table.width( i ) ) << alignment << row[ i ];
            stream << table.vertical();
        }
        stream << "\n";
		if (table.has_ruler()) {
        	stream << table.ruler() << "\n";
		}
    }

    return stream;
}

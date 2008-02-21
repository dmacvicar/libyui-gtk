/********************************************************************
 *           YaST2-GTK - http://en.opensuse.org/YaST2-GTK           *
 ********************************************************************/

#include <config.h>
#include <stdio.h>
#include <string.h>
#include <YUI.h>
#include <gtk/gtk.h>
#include <YGUtils.h>

bool testMapKBAccel()
{
	fprintf (stderr, "Test map KB accels\t");
	struct {
		const char *in;
		const char *out;
	} aTests[] = {
		{ "Foo&", "Foo_" },
		{ "B&aa", "B_aa" },
		{ "&Foo", "_Foo" },
		{ "_Foo", "__Foo" },
// FIXME - unfortunately it seems yast has noescaping policy
// for labels (hmm) at least judging from the code at
// ncurses/src/NCstring.cc (getHotKey)
//		{ "&&Foo", "&Foo" },
		{ NULL, NULL }
	};
	for (int i = 0; aTests[i].in; i++) {
		string mapped = YGUtils::mapKBAccel(aTests[i].in);
		if (mapped != aTests[i].out) {
			fprintf (stderr, "Mis-mapped accel '%s' vs '%s'\n",
				 mapped.c_str(), aTests[i].out);
			return false;
		}
		fprintf (stderr, "%d ", i);
	}
	fprintf (stderr, "\n");
	return true;
}

bool testXHtmlConvert()
{
	fprintf (stderr, "Test HTML->XML rewrite \t");
	struct {
		const char *in;
		const char *out;
	} aTests[] = {
		// preservation
		{ "<p>foo</p>", "<body><p>foo</p></body>" },
/*		// product substitution
		{ "&product;", "<body>foo</body>" },
		{ " <p>&product;</p>", "<body><p>foo</p></body>" },*/
		// outer tag
		{ "some text", "<body>some text</body>" },
		// unquoted attributes
		{ "<foo baa=Foo></foo>", "<body><foo baa=\"Foo\"></foo></body>" },
		// break tags
		{ "<br>", "<body><br/></body>" },
		{ "<hr>", "<body><hr/></body>" },
		// unclosed tags
		{ "<p>", "<body><p></p></body>" },
		{ "<b>unclosed", "<body><b>unclosed</b></body>" },
		{ "<b><i>bold</i>", "<body><b><i>bold</i></b></body>" },
		{ "<i><i>bold</i>", "<body><i><i>bold</i></i></body>" },
		{ "<unclosed foo=baa>",
		  "<body><unclosed foo=\"baa\"></unclosed></body>" },
		// unclosed 'early close' tags
		{ "<i>Some<p>text<p> here<p></i>",
		  "<body><i>Some<p>text</p><p> here</p><p></p></i></body>" },
		{ "<ul><li>foo<li>baa",
		  "<body><ul><li>foo</li><li>baa</li></ul></body>" },
		{ "no outer<p>unclosed<p>several<b>unclosed bold",
		  "<body>no outer<p>unclosed</p><p>several<b>unclosed bold</b></p></body>" },
		// multiple white spacing -- proper HTML would had collapsed those multiple
		// spaces -- not important anyway
		{ "one   day  I  will do", "<body>one   day  I  will do</body>" },
		// comment
		{ "we need <b>to <!-- really need to? --> do something</b> about it.",
		  "<body>we need <b>to  do something</b> about it.</body>" },
		{ NULL, NULL }
	};
	for (int i = 0; aTests[i].in; i++) {
		gchar *out = ygutils_convert_to_xhmlt_and_subst (aTests[i].in, "foo");
		if (strcmp (out, aTests[i].out)) {
			fprintf (stderr, "Mis-converted entry %d XML '%s' should be '%s'\n",
				 i, out, aTests[i].out);
			return false;
		}
		fprintf (stderr, "%d ", i);
		g_free (out);
	}
	fprintf (stderr, "\n");
	return true;
}

bool testMarkupEscape()
{
	fprintf (stderr, "Test markup escape\t");
	struct {
		const char *in;
		const char *out;
		bool escape_br;
	} aTests[] = {
		{ "< text />", "&lt; text /&gt;" },
		{ "um\ndois\ntres", "um\ndois\ntres" },
		{ NULL, NULL }
	};
	for (int i = 0; aTests[i].in; i++) {
		string out (aTests[i].in);
		YGUtils::escapeMarkup (out);
		if (out != aTests[i].out) {
			fprintf (stderr, "Mis-converted entry %d XML '%s' should be '%s'\n",
				 i, out.c_str(), aTests[i].out);
			return false;
		}
		fprintf (stderr, "%d ", i);
	}
	fprintf (stderr, "\n");
	return true;
}

int main (int argc, char **argv)
{
	bool bSuccess = true;

	bSuccess &= testMapKBAccel();
	bSuccess &= testXHtmlConvert();
	bSuccess &= testMarkupEscape();

	return !bSuccess;
}


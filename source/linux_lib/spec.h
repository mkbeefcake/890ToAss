#ifndef WIN32
#ifndef SPEC_H_
#define SPEC_H_

/*
 * Matches the regular language accepted by findfirst/findnext. More
 * precisely, * matches zero or more characters and ? matches any
 * characters, but only one. Every other characters match themself.
 * To respect the Windows behavior, *.* matches everything.
 */
int match_spec(const char* spec, const char* text);

#endif /* SPEC_H_ */
#endif

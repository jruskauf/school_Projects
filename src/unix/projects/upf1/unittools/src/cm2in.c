#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>
#include "unittools.h"

#define  CONVERT     2.54
#define  DELIM       " -> "
#define  SRCUNITNAME "centimeters"
#define  SRCUNIT     "cm"
#define  DSTUNITNAME "inches"
#define  DSTUNIT     "in"

typedef unsigned char uc;
typedef unsigned int  ui;

void usage (char *);

int main (int argc, char **argv)
{
    //////////////////////////////////////////////////////////////////
    //
    // Declare variables
    //
    char        string[25];
    char        number[25];
    char        unit[4];
    char       *delim               = NULL;
    char       *idelim              = NULL;
    char       *input               = NULL;
    char       *loc                 = NULL;
    char       *regex               = NULL;
    char       *rpos                = NULL;
    char       *str                 = NULL;
    char        space               = ' ';
    char        unitflag            = 0;
    char        verbose             = 0;
    double      value               = 0.0;
    double      source              = 0.0;
    FILE       *inp                 = NULL;
    FILE       *out                 = stdout;
    int         count               = -1;
    int         opt                 = 0;
    int         status              = 0;
    size_t      numgrps             = 3;
    size_t      size                = 0;
    uc          precis              = PRECIS;
    ui          offset              = 0;
    regex_t     rgi;
    regmatch_t  grp[numgrps];

    //////////////////////////////////////////////////////////////////
    //
    // Argument processing loop
    //
    while ((opt = getopt (argc, argv, "I:d:hnNp:qvV")) != -1)
    {
        switch (opt)
        {
            case 'I':
                idelim              = optarg;
                break;

            case 'd':
                delim               = optarg;
                break;

            case 'h':
                usage (*argv);
                exit (0);

            case 'n':
                unitflag            = 1;
                break;

            case 'N':
                space               = '\b';
                break;

            case 'p':
                sscanf (optarg, "%[0123456789]", string);
                precis              = atoi (string);
                break;

            case 'q':
                out                 = fopen ("/dev/null", "w");
                break;

            case 'v':
                verbose             = verbose + 1;
                if (verbose        >  1)
                    count           = 0;
                break;

            case 'V':
                fprintf (stdout, "%s (%s), version %s\n", *(argv+0), NAME, VERSION);
                exit (0);

            default:
                exit (1);
        }
    }

    //////////////////////////////////////////////////////////////////
    //
    // If output delimiter is not set, set it to default delimiter
    //
    if (delim                      == NULL)
    {
        delim                       = (char *) malloc (sizeof (char) * 5);
        strcat (delim, DELIM);
    }

    //////////////////////////////////////////////////////////////////
    //
    // If input delimiter is not set, set it to default delimiter
    //
    if (idelim                     == NULL)
    {
        idelim                      = (char *) malloc (sizeof (char) * 5);
        strcat (idelim, DELIM);
    }

    //////////////////////////////////////////////////////////////////
    //
    // Determine our source of input, STDIN or file
    //
    if (*(argv+optind)             == NULL)
        inp                         = stdin;
    else
    {
        inp                         = fopen (*(argv+optind), "r");
        if (inp                    == NULL)
        {
            fprintf (stderr, "Error opening input file '%s'\n", *(argv+optind));
            exit (1);
        }
    }

    //////////////////////////////////////////////////////////////////
    //
    // If PRECIS environment variable is set, override precision
    //
    str                             = getenv ("PRECIS");
    if (str                        != NULL)
        precis                      = atoi (str);

    //////////////////////////////////////////////////////////////////
    //
    // Build regex pattern based on input delimiter
    //
    size                            = sizeof (char) * (30 + strlen (idelim));
    regex                           = (char *) malloc (size);
    sprintf (regex, "([0-9]*.?[0-9]*) *([A-Za-z]*)(%s)*", idelim);

    //////////////////////////////////////////////////////////////////
    //
    // Compile and verify regex pattern
    //
    status                          = regcomp (&rgi, regex, REG_EXTENDED);
    if (status                     != 0)
    {
        fprintf (stderr, "Could not compile regular expression.\n");
        return (1);
    }

    //////////////////////////////////////////////////////////////////
    //
    // Set up to process input data, and grab it
    //
    opt                             = -2;
    input                           = (char *) malloc (sizeof(char)*BUFFER);
    fgets (input, BUFFER, inp); 
    loc                             = input;

    //////////////////////////////////////////////////////////////////
    //
    // Input processing
    //
    status                          = regexec(&rgi, loc, numgrps, grp, 0);
    offset                          = 0;
    while ((status                 != REG_NOMATCH) &&
           (*(loc+offset)          != '\0'))
    {
        offset                      = grp[0].rm_eo;

        size                        = sizeof (char) * (strlen (loc) + 1);
        rpos                        = (char *) malloc (size);
        strcpy(rpos, loc);
        rpos[grp[1].rm_eo]          = 0;

        if (*(rpos + grp[1].rm_so) == '\n')
            break;

        strcpy (number, rpos + grp[1].rm_so);
        fprintf (out, "%s", number);
        strcpy(rpos, loc);
        rpos[grp[2].rm_eo]          = 0;
        strcpy (unit, rpos + grp[2].rm_so);
        if ((space                 == 32) &&
            (unit[0]               != '\0'))
        {
            fprintf (out, " ");
        }
        fprintf (out, "%s%s", unit, delim);
        loc                         = loc + offset;
        status                      = regexec(&rgi, loc, numgrps, grp, 0);
        offset                      = 0;
    }

    //////////////////////////////////////////////////////////////////
    //
    // Obtain source data and convert to destination value
    //
    source                          = atof (number);
    value                           = source / CONVERT;

    //////////////////////////////////////////////////////////////////
    //
    // Display destination value
    //
    fprintf (out, "%.*lf",   precis, value);

    if ((unit[0]                   == '\0') ||
		(strcmp (unit, SRCUNIT)    == 0))
    {
        if (unitflag               == 0)
        {
            if (space              == 32)
                fprintf (out, " ");
            fprintf (out, "%s", DSTUNIT);
        }
    }
    else
    {
        fprintf (stderr, "\n\nERROR: Invalid source unit!\n");
        exit (1);
    }
    fprintf (out, "\n");

    if (count                      != -1)
        count                       = count + 1;

    //////////////////////////////////////////////////////////////////
    //
    // If enabled, display a count
    //
    if (count                      != -1)
    {
        fprintf (out, "Processed %d item", count);
        if (count                  != 1)
            fprintf (out, "s");
        fprintf (out, ".\n");
    }

    //////////////////////////////////////////////////////////////////
    //
    // Close custom file pointers and free regex resources
    //
    regfree (&rgi);
    fclose (inp);
    fclose (out);

    return (0);
}

void usage(char *argv)
{
    fprintf (stdout, "Usage: %s [OPTION]... [FILE]\n", argv);
    fprintf (stdout, "Convert %s (%s) to %s (%s)\n\n", SRCUNITNAME, SRCUNIT, 
                                                      DSTUNITNAME, DSTUNIT);
    fprintf (stdout, "  -I \"DELIM\"   set input delimiter  (default: \"%s\")\n", DELIM);
    fprintf (stdout, "  -d \"DELIM\"   set output delimiter (default: \"%s\")\n", DELIM);
    fprintf (stdout, "  -h           display this help and exit\n");
    fprintf (stdout, "  -n           do not display units\n");
    fprintf (stdout, "  -N           no space between value and unit\n");
    fprintf (stdout, "  -p POINTS    set output precision (default: %d)\n", PRECIS);
    fprintf (stdout, "  -q           quiet, do not display anything\n");
    fprintf (stdout, "  -v           verbose, display more information\n");
    fprintf (stdout, "  -V           display version information and exit\n\n");
    fprintf (stdout, "Verbosity compounds; first it will display source data,\n");
    fprintf (stdout, "next it will add a count of items processed.\n");
}

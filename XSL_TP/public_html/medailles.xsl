<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : medailles.xsl
    Created on : 23 septembre 2021, 15:35
    Author     : ntessier
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet version = '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
    <xsl:template match="bibliotheque">
        <html>
            <head>
                
                <link href="medailles.css" type="text/css" rel="stylesheet" />
                
            </head>
            <body>
                <table>        
                    <tr>
                        <th>Pays</th>
                        <th>Or</th>
                        <th>Argent</th>
                        <th>Bronze</th>
                    </tr>
                    <xsl:apply-templates />
                </table>
            </body>
        </html>
    </xsl:template>
    
    <xsl:template match="ligne">
        <tr>
            <xsl:apply-templates />
        </tr>
    </xsl:template>
    
    <xsl:template match="pays">
        <td>
            <xsl:value-of select="@nomDePays" />
        </td>
    </xsl:template>
    
    <xsl:template match="medaille">
        <td>
            <xsl:value-of select="@or" />
        </td>
        <td>
            <xsl:value-of select="@argent" />
        </td>
        <td>
            <xsl:value-of select="@bronze" />
        </td>
    </xsl:template>
    
    
   
</xsl:stylesheet>
    

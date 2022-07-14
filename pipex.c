/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satouaya <satouaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:11:01 by aysato            #+#    #+#             */
/*   Updated: 2022/07/14 17:03:38 by satouaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <stdlib.h>
   	#include <unistd.h>     /* pipe() */
   	#include <sys/types.h>  /* pid_t */
	
	extern  void parent( int fildes[2] );
	extern  void child( int fildes[2] );	
	int main()
	{
	    int fildes[2] ;
	    pid_t pid ;
	
	        if( pipe(fildes) == -1)
	        {
	            perror("pipe");
	            exit( 1 );
	        }
	        /* fildes[0] -- 読み込み用
	         * fildes[1] -- 書き込み用	         */
	        if( (pid=fork()) == 0 )
	        {
	            child( fildes );
	            exit( 0 );
        }
	        else if( pid > 0 )
	        {
	            parent( fildes );
	            wait( 0 );
	        }
	        else
	        {
	            perror("fork");
	            exit( 1 );
	        }
	}
	
	void parent( int fildes[2] )
	{
	    char *p, c ;
	        close( fildes[0] );
	        p = "hello,world\n" ;
	        while( *p )
	        {
	            c = *p ++ ;
	            write( fildes[1],&c,1 );
	        }
	        close( fildes[1] );
	}
	
	void child( int fildes[2] )
	{
	    char c, c2 ;
	        close( fildes[1] );
	        while( read(fildes[0],&c,1) >0 )
	        {
	            c2 = toupper(c);
	            write( 1, &c2, 1 );
	        }
	        close( fildes[0] );
  	}
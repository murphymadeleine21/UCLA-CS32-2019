//
//  list.cpp
//  Homework 4
//
//  Created by Madeleine Murphy on 5/27/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//


void listAll(const Domain* d, string path) // two-parameter overload
{
    //You will write this code.
    vector<Domain*> sub = d->subdomains();
    vector<Domain*>::const_iterator it = sub.begin();
    //path = d->label();
    if (sub.empty()){
        cout << path << endl;
    }
    for (; it != sub.end(); it++)
    {
        Domain* dit = *it;
        if (path == "")
            listAll(dit, dit->label());
        else
            listAll(dit, dit->label() + '.' + path);
    }
    
}

//
//  Blender2OpenGl.cpp
//  Blender2OpenGl
//
//  Created by Rae, Ethan on 10/31/14.

//----------------------------------------------------------------------------
// read an obj model file
//----------------------------------------------------------------------------

#include <iostream>
using namespace std;
#include "ReadModel.h"
vector<vec4> verts_;
vector<vec3> norms_;
vector<vec2> uvs_;
vector<int> v_indices_;
vector<int> n_indices_;
vector<int> uv_indices_;

vector<vec4> vertex_buffer_;
vector<vec3> normal_buffer_;
vector<vec2> uvs_buffer_;
//vector<vec4> indices_buffer;
//vector<vec4> weights_buffer;

std::string::size_type sz1_, sz2_, sz3_, sz4_, sz5_, sz6_, sz7_, sz8_;
void
ReadModel2( Model* m, char* c)
{
    verts_.clear();
    norms_.clear();
    uvs_.clear();
    
    uv_indices_.clear();
    v_indices_.clear();
    n_indices_.clear();
   
    vertex_buffer_.clear();
    normal_buffer_.clear();
    uvs_buffer_.clear();
    
    
    string line;
    ifstream myfile (c);

    if (myfile.is_open())
    {
        // read the data into vectors
        while ( getline (myfile,line) )
        {
            string l = &(line[2]);
            if (line[0] == 'v' && line[1] == ' ')
            {
                verts_.push_back( vec4( stof(l,&sz1_), stof(l.substr(sz1_),&sz2_), stof(l.substr(sz1_+sz2_)), 1.0 ) );
            }
            else
            {
                if (line[0] == 'v' && line[1] == 'n')
                {
                    norms_.push_back( vec3( stof(l,&sz1_), stof(l.substr(sz1_),&sz2_), stof(l.substr(sz1_+sz2_)) ) );
                    //cout << norms_.back() << endl;
                }
                else
                {
                    if(line[0] == 'v' && line[1] == 't')
                    {
                        uvs_.push_back( vec2(stof(l,&sz1_), stof(l.substr(sz1_),&sz2_) ) );
                     //   cout << uvs_.back() << '\n' << endl;
                    }
                    else
                    {
                        if (line[0] == 'f' && line[1] == ' ')
                        {
                            //f 1986//1 254//2 6//3
                            //f 321/213/323 325/197/320 343/202/341
                            v_indices_.push_back(stoi(l,&sz1_));
                            uv_indices_.push_back(stoi(l.substr(sz1_+1),&sz2_));
                            n_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1),&sz3_));
                            
                            v_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_),&sz4_));
                            uv_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_+sz4_+1),&sz5_));
                            n_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_+sz4_+1+sz5_+1),&sz6_));
                            
                            v_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_+sz4_+1+sz5_+1+sz6_),&sz7_));
                            uv_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_+sz4_+1+sz5_+1+sz6_+sz7_+1),&sz8_));
                            n_indices_.push_back(stoi(l.substr(sz1_+1+sz2_+1+sz3_+sz4_+1+sz5_+1+sz6_+sz7_+1+sz8_+1)));
                        }
                    }
                }
            }
        }
        myfile.close();
        
        // assign the data to the Model
        
        m->num_vertices = v_indices_.size();
        m->ogl_v_size = m->num_vertices * sizeof(vec4);
        m->ogl_n_size = m->num_vertices * sizeof(vec3);
        m->ogl_uv_size = m->num_vertices * sizeof(vec2);
        
        for( int i = 0; i < m->num_vertices; i++ )
        {
            vertex_buffer_.push_back( verts_[v_indices_[i]-1] );
            //cout << i << ' ' << v_indices_[i] << ' ' << vertex_buffer_.back() << endl;
            
            normal_buffer_.push_back( norms_[n_indices_[i]-1] );
            //cout << norms_.back() << endl;
            
            uvs_buffer_.push_back(uvs_[uv_indices_[i]-1]);
            
        }
        
        m->vertices = vertex_buffer_.data();
        m->normals = normal_buffer_.data();
        m->uvs = uvs_buffer_.data();
    }
    else
        cout << "Unable to open file" << endl;
    
    //---- allocate buffers for indices and weights
    m->indices = new vec4[m->num_vertices];
    m->weights = new vec4[m->num_vertices];
    m->ogl_i_size = m->num_vertices * sizeof(vec4);
    m->ogl_w_size = m->num_vertices * sizeof(vec4);
    
}

void ReadModel( Model* m, char* c)
{
    verts_.clear();
    norms_.clear();
    uvs_.clear();
    
    v_indices_.clear();
    n_indices_.clear();
    
    vertex_buffer_.clear();
    normal_buffer_.clear();
    uvs_buffer_.clear();
    
    
    string line;
    ifstream myfile (c);
    
    if (myfile.is_open())
    {
        // read the data into vectors
        while ( getline (myfile,line) )
        {
            string l = &(line[2]);
            if (line[0] == 'v' && line[1] == ' ')
            {
                verts_.push_back( vec4( stof(l,&sz1_), stof(l.substr(sz1_),&sz2_), stof(l.substr(sz1_+sz2_)), 1.0 ) );
                
                uvs_.push_back( uv( vec4( stof(l,&sz1_), stof(l.substr(sz1_),&sz2_), stof(l.substr(sz1_+sz2_)), 1.0 )));
            }
            else
            {
                if (line[0] == 'v' && line[1] == 'n')
                {
                    norms_.push_back( vec3( stof(l,&sz1_), stof(l.substr(sz1_),&sz2_), stof(l.substr(sz1_+sz2_)) ) );
                    //cout << norms.back() << endl;
                }
                else
                {
                    if (line[0] == 'f' && line[1] == ' ')
                    {
                        v_indices_.push_back(stoi(l,&sz1_));
                        n_indices_.push_back(stoi(l.substr(sz1_+2),&sz2_));
                        v_indices_.push_back(stoi(l.substr(sz1_+2+sz2_),&sz3_));
                        n_indices_.push_back(stoi(l.substr(sz1_+2+sz2_+sz3_+2),&sz4_));
                        v_indices_.push_back(stoi(l.substr(sz1_+2+sz2_+sz3_+2+sz4_),&sz5_));
                        n_indices_.push_back(stoi(l.substr(sz1_+2+sz2_+sz3_+2+sz4_+sz5_+2)));
                    }
                }
            }
        }
        myfile.close();
        
        // assign the data to the Model
        
        m->num_vertices = v_indices_.size();
        m->ogl_v_size = m->num_vertices * sizeof(vec4);
        m->ogl_n_size = m->num_vertices * sizeof(vec3);
        m->ogl_uv_size = m->num_vertices * sizeof(vec2);
        
        for( int i = 0; i < m->num_vertices; i++ )
        {
            vertex_buffer_.push_back( verts_[v_indices_[i]-1] );
            //cout << i << ' ' << v_indices[i] << ' ' << vertex_buffer.back() << endl;
            
            normal_buffer_.push_back( norms_[n_indices_[i]-1] );
            //cout << norms.back() << endl;
            
            uvs_buffer_.push_back(uvs_[v_indices_[i]-1]);
            
        }
        
        m->vertices = vertex_buffer_.data();
        m->normals = normal_buffer_.data();
        m->uvs = uvs_buffer_.data();
    }
    else
        cout << "Unable to open file" << endl;
    
    //---- allocate buffers for indices and weights
    m->indices = new vec4[m->num_vertices];
    m->weights = new vec4[m->num_vertices];
    m->ogl_i_size = m->num_vertices * sizeof(vec4);
    m->ogl_w_size = m->num_vertices * sizeof(vec4);
    
}